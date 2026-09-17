#!/usr/bin/env python3
"""
图书馆座位预约 API 服务器
========================
用法:
  python server.py [--host 127.0.0.1] [--port 8000]

接口一览:
  GET  /                     前端页面 (static/index.html)
  GET  /api/status           凭证/登录/轮询状态
  POST /api/login            触发浏览器登录 (异步, 弹出浏览器窗口)
  GET  /api/login/status     登录进度 (stage: login/done/warn/error/idle)
  POST /api/login/cancel     取消登录 (关闭浏览器)
  GET  /api/rooms            房间列表
  GET  /api/config           当前配置
  POST /api/config           保存配置
  GET  /api/seats            查询座位列表 (座位名 -> devId)
  POST /api/reserve/start    启动轮询预约 (异步)
  POST /api/reserve/stop     停止轮询
  GET  /api/reserve/status   轮询状态
  GET  /api/logs             拉取日志
"""
import os
import sys
import time
import threading
from pathlib import Path
from typing import Optional

from fastapi import FastAPI, HTTPException
from fastapi.responses import FileResponse, JSONResponse
from fastapi.staticfiles import StaticFiles
from pydantic import BaseModel

# PyInstaller 打包后静态资源解压到 _MEIPASS/static
BASE_DIR = Path(getattr(sys, "_MEIPASS", Path(__file__).parent))
STATIC_DIR = BASE_DIR / "static"

from config import Config
from reserve import (
    LibSeatAPI, browser_login, load_credentials, save_credentials,
    polling_reserve, LOG_BUFFER,
)

app = FastAPI(title="图书馆座位预约")

# ============================================================
# 全局状态 (线程安全)
# ============================================================
_lock = threading.Lock()

_login = {
    "running": False,
    "stage": "idle",          # idle/login/done/warn/error
    "message": "",
    "error": "",
    "cancel_event": None,
    "user_info": None,
}
_poll = {
    "running": False,
    "success": None,          # None=进行中 True=成功 False=失败
    "message": "",
    "seat_ids": [],
    "stop_event": None,
}


def get_api_client() -> LibSeatAPI | None:
    """根据凭证文件创建一个可用的 API 客户端"""
    cfg = Config.load()
    path = cfg.cookies_file
    if not os.path.exists(path):
        return None
    cookies, user_info = load_credentials(path)
    if not cookies:
        return None
    acc_no = user_info.get("accNo") or cfg.app_acc_no
    token = user_info.get("token", "") or ""
    return LibSeatAPI(cfg.api_base, cookies, timeout=cfg.timeout,
                      app_acc_no=acc_no, token=token)


def check_authenticated() -> dict | None:
    """返回 user 信息 dict, 未登录返回 None"""
    cfg = Config.load()
    path = cfg.cookies_file
    if not os.path.exists(path):
        return None
    cookies, user_info = load_credentials(path)
    if not cookies:
        return None
    api = LibSeatAPI(cfg.api_base, cookies, timeout=cfg.timeout,
                     app_acc_no=user_info.get("accNo"), token=user_info.get("token", ""))
    if not api.check_alive():
        return None
    token = user_info.get("token", "") or ""
    return {
        "accNo": user_info.get("accNo"),
        "trueName": user_info.get("trueName", ""),
        "token_masked": token[:8] + "..." if token else "",
    }


# ============================================================
# 登录线程
# ============================================================
def login_worker(cfg: Config):
    cancel_event = threading.Event()
    with _lock:
        _login["running"] = True
        _login["stage"] = "login"
        _login["message"] = "正在启动登录..."
        _login["error"] = ""
        _login["cancel_event"] = cancel_event

    def progress_cb(stage: str, message: str):
        with _lock:
            _login["stage"] = stage
            _login["message"] = message

    try:
        cookies, user_info = browser_login(
            auth_url=cfg.auth_url,
            target_url=f"{cfg.api_base.split('/ic-web')[0]}/",
            chromedriver_path=cfg.chromedriver,
            progress_cb=progress_cb,
            cancel_event=cancel_event,
        )
        if not cookies:
            with _lock:
                _login["stage"] = "error" if _login["stage"] != "error" else "error"
                _login["message"] = "登录已取消或未获取到 cookies"
            return

        # 保存凭证 (核心成果, 成功后标记 done)
        save_credentials(cfg.cookies_file, cookies, user_info)
        with _lock:
            _login["stage"] = "done"
            _login["message"] = f"登录成功! 用户: {user_info.get('trueName', '')}"
            _login["user_info"] = user_info

        # 更新 accNo 到配置 (失败不影响登录成功状态)
        try:
            if user_info.get("accNo"):
                cfg.app_acc_no = str(user_info["accNo"])
                cfg.save()
        except Exception as exc:
            log.warning(f"更新配置中的 accNo 失败 (不影响登录): {exc}")

    except Exception as exc:
        with _lock:
            _login["stage"] = "error"
            _login["message"] = f"登录过程异常: {exc}"
            _login["error"] = str(exc)
        log_error(f"登录异常: {exc}")
    finally:
        with _lock:
            _login["running"] = False
            _login["cancel_event"] = None


def log_error(msg: str):
    import logging
    logging.getLogger("libseat").error(msg)


# ============================================================
# 轮询线程
# ============================================================
def poll_worker(cfg: Config, seat_ids: list[str], interval: float, max_retry: int):
    stop_event = threading.Event()
    with _lock:
        _poll["running"] = True
        _poll["success"] = None
        _poll["message"] = "轮询中..."
        _poll["seat_ids"] = seat_ids
        _poll["stop_event"] = stop_event

    try:
        api = get_api_client()
        if api is None:
            with _lock:
                _poll["message"] = "未找到有效凭证, 请先登录"
            return

        start_time, end_time = compute_time_range(cfg.booking_time, cfg.booking_duration)
        success = polling_reserve(
            api=api,
            room_id=cfg.room_id,
            seat_ids=seat_ids,
            date=cfg.date,
            start_time=start_time,
            end_time=end_time,
            interval=interval,
            max_retry=max_retry,
            stop_event=stop_event,
        )
        with _lock:
            _poll["success"] = success
            _poll["message"] = "预约成功!" if success else "预约未成功"
    except Exception as exc:
        with _lock:
            _poll["success"] = False
            _poll["message"] = f"轮询异常: {exc}"
    finally:
        with _lock:
            _poll["running"] = False
            _poll["stop_event"] = None


def compute_time_range(booking_time: str, duration_min: int):
    from datetime import datetime, timedelta
    h, m = map(int, booking_time.split(":"))
    start_dt = datetime(2026, 1, 1, h, m)
    end_dt = start_dt + timedelta(minutes=duration_min)
    return start_dt.strftime("%H:%M"), end_dt.strftime("%H:%M")


# ============================================================
# 请求模型
# ============================================================
class ConfigUpdate(BaseModel):
    room_id: Optional[str] = None
    date: Optional[str] = None
    seat_ids: Optional[list] = None
    booking_time: Optional[str] = None
    booking_duration: Optional[int] = None
    poll_interval: Optional[float] = None
    max_retry: Optional[int] = None
    seat_keyword: Optional[str] = None


class ReserveStart(BaseModel):
    seat_ids: list[str]
    interval: float = 0.3
    max_retry: int = 100


# ============================================================
# 页面 & 房间
# ============================================================
@app.get("/", include_in_schema=False)
def index():
    return FileResponse(STATIC_DIR / "index.html")


app.mount("/static", StaticFiles(directory=str(STATIC_DIR)), name="static")


@app.get("/api/rooms")
def rooms():
    from config import ROOMS
    return [{"id": rid, "name": name} for name, rid in ROOMS]


# ============================================================
# 状态 & 登录
# ============================================================
@app.get("/api/status")
def status():
    with _lock:
        login_snap = dict(_login)
        poll_snap = dict(_poll)
    user = check_authenticated()
    return {
        "authenticated": user is not None,
        "user": user,
        "login": {
            "running": login_snap["running"],
            "stage": login_snap["stage"],
            "message": login_snap["message"],
        },
        "reserve": {"running": poll_snap["running"]},
    }


@app.post("/api/login")
def start_login():
    with _lock:
        if _login["running"]:
            raise HTTPException(409, "登录已在进行中")
    cfg = Config.load()
    threading.Thread(target=login_worker, args=(cfg,), daemon=True).start()
    return {"started": True}


@app.get("/api/login/status")
def login_status():
    with _lock:
        return {
            "running": _login["running"],
            "stage": _login["stage"],
            "message": _login["message"],
            "error": _login["error"],
        }


@app.post("/api/login/cancel")
def cancel_login():
    with _lock:
        ev = _login.get("cancel_event")
        running = _login["running"]
        _login["stage"] = "error"
        _login["message"] = "已请求取消登录"
    if ev is not None and running:
        ev.set()
    return {"cancelled": True}


# ============================================================
# 配置
# ============================================================
@app.get("/api/config")
def config_get():
    cfg = Config.load()
    return {
        "room_id": cfg.room_id,
        "date": cfg.date,
        "seat_ids": cfg.seat_ids,
        "booking_time": cfg.booking_time,
        "booking_duration": cfg.booking_duration,
        "poll_interval": cfg.poll_interval,
        "max_retry": cfg.max_retry,
        "seat_keyword": cfg.seat_keyword,
        "app_acc_no": cfg.app_acc_no,
    }


@app.post("/api/config")
def config_save(update: ConfigUpdate):
    cfg = Config.load()
    data = update.dict(exclude_unset=True)
    for k, v in data.items():
        if hasattr(cfg, k):
            setattr(cfg, k, v)
    cfg.save()
    return {"saved": True, "config": config_get()}


# ============================================================
# 座位查询
# ============================================================
@app.get("/api/seats")
def seats(room_id: str, date: str):
    api = get_api_client()
    if api is None:
        raise HTTPException(401, "未登录或凭证无效, 请先登录")
    try:
        result = api.get_reserve_list(room_id, date)
        code = (result or {}).get("code")
        if code not in (0, 200, "0", "200"):
            return JSONResponse(status_code=400, content={
                "detail": f"查询座位列表失败 (code={code}): {(result or {}).get('message', '')}"
            })
        raw = (result or {}).get("data") or []
        seat_list = []
        for s in raw:
            if isinstance(s, dict):
                name = s.get("devName") or s.get("seatName") or s.get("name")
                dev_id = s.get("devId") or s.get("id") or s.get("seatId")
                if name and dev_id:
                    seat_list.append({"id": str(dev_id), "name": str(name)})
        return {"seats": seat_list, "error": ""}
    except Exception as exc:
        return JSONResponse(status_code=502, content={"detail": f"查询座位失败: {exc}"})


# ============================================================
# 预约轮询
# ============================================================
@app.post("/api/reserve/start")
def reserve_start(req: ReserveStart):
    with _lock:
        if _poll["running"]:
            raise HTTPException(409, "轮询已在运行中")
    if get_api_client() is None:
        raise HTTPException(401, "未登录或凭证无效, 请先登录")
    cfg = Config.load()
    threading.Thread(target=poll_worker,
                     args=(cfg, req.seat_ids, req.interval, req.max_retry),
                     daemon=True).start()
    return {"started": True}


@app.post("/api/reserve/stop")
def reserve_stop():
    with _lock:
        ev = _poll.get("stop_event")
        running = _poll["running"]
        _poll["message"] = "已请求停止"
    if ev is not None and running:
        ev.set()
    return {"stopped": True}


@app.get("/api/reserve/status")
def reserve_status():
    with _lock:
        return {
            "running": _poll["running"],
            "success": _poll["success"],
            "message": _poll["message"],
            "seat_ids": _poll["seat_ids"],
        }


# ============================================================
# 日志
# ============================================================
@app.get("/api/logs")
def logs(after: int = 0, n: int = 200):
    entries = LOG_BUFFER.tail(n)
    return {"logs": entries, "has_more": False}


# ============================================================
# 入口
# ============================================================
def find_free_port(start: int, max_tries: int = 50) -> int:
    """从 start 端口开始逐个探测, 返回第一个空闲端口 (TIME_WAIT 不影响)"""
    import socket
    for port in range(start, start + max_tries):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            try:
                s.bind(("127.0.0.1", port))
                return port
            except OSError:
                continue
    raise RuntimeError(f"从端口 {start} 起连续 {max_tries} 个端口均被占用")


def main():
    import argparse
    import uvicorn
    parser = argparse.ArgumentParser(description="图书馆座位预约 API 服务器")
    parser.add_argument("--host", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=8000, help="起始端口, 被占用则自动递增")
    parser.add_argument("--reload", action="store_true", help="开发模式热重载")
    args = parser.parse_args()

    port = find_free_port(args.port)
    if port != args.port:
        print(f"⚠️  端口 {args.port} 已被占用, 自动改用 {port}")
    print(f"\n🔌 图书馆座位预约服务器: http://{args.host}:{port}")
    print("   打开浏览器访问上述地址即可使用。\n")
    uvicorn.run(app, host=args.host, port=port, reload=args.reload)


if __name__ == "__main__":
    main()