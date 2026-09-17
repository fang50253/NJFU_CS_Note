#!/usr/bin/env python3
"""
南京林业大学图书馆座位预约脚本
=================================
功能:
  1. Selenium 弹出浏览器, 用户手动登录
  2. 自动获取 session cookies
  3. 交互式选择座位 / 时间
  4. 定时轮询抢座

使用方法:
  python reserve.py                  # 正常流程
  python reserve.py --config         # 修改配置
  python reserve.py --show-cookies   # 仅登录获取cookies (调试)

环境变量:
  LIBSEAT_ROOM_ID=111488396
  LIBSEAT_DATE=20260909
  LIBSEAT_SEAT_IDS=111488400,111488401
  LIBSEAT_POLL_INTERVAL=0.3
  LIBSEAT_START_HOUR=22
  LIBSEAT_START_MINUTE=0
  LIBSEAT_BOOKING_TIME=08:00
  LIBSEAT_BOOKING_DURATION=300
  LIBSEAT_SEAT_KEYWORD=七楼
  LIBSEAT_CHROMEDRIVER=/path/to/chromedriver
"""

import sys
import os
import time
import json
import argparse
import logging
from datetime import datetime, timedelta
from typing import Optional
from urllib.parse import urljoin, urlencode

import requests

# ============================================================
# 日志
# ============================================================
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%H:%M:%S",
)
log = logging.getLogger("libseat")


class LogBuffer(logging.Handler):
    """内存日志环形缓冲, 供 API 服务器轮询拉取"""

    def __init__(self, maxlen: int = 500):
        super().__init__()
        self.buffer = []
        self.maxlen = maxlen

    def emit(self, record: logging.LogRecord):
        entry = {
            "time": self.format(record)[:19],
            "level": record.levelname,
            "message": record.getMessage(),
        }
        self.buffer.append(entry)
        if len(self.buffer) > self.maxlen:
            self.buffer = self.buffer[-self.maxlen:]

    def tail(self, n: int = 100) -> list:
        return self.buffer[-n:]


LOG_BUFFER = LogBuffer()
LOG_BUFFER.setFormatter(logging.Formatter("%(asctime)s", datefmt="%H:%M:%S"))
log.addHandler(LOG_BUFFER)

# ============================================================
# Selenium 浏览器登录
# ============================================================

def browser_login(auth_url: str, target_url: str, chromedriver_path: str = "",
                  progress_cb=None, cancel_event=None) -> tuple[dict, dict]:
    """
    打开浏览器让用户登录, 返回 (cookies, userInfo dict)
    progress_cb: 可选回调, 接收 (阶段, 消息) 用于上报登录进度
    cancel_event: 可选 threading.Event, 设置后中止等待并关闭浏览器
    """
    try:
        from selenium import webdriver
        from selenium.webdriver.chrome.options import Options
        from selenium.webdriver.chrome.service import Service
        from selenium.webdriver.common.by import By
        from selenium.webdriver.support.ui import WebDriverWait
        from selenium.webdriver.support import expected_conditions as EC
    except ImportError:
        log.error("需要安装 selenium: pip install selenium")
        log.error("还需要安装对应版本的 chromedriver")
        sys.exit(1)

    opts = Options()
    # 登录必须有界面
    opts.add_argument("--no-sandbox")
    opts.add_argument("--disable-dev-shm-usage")
    opts.add_argument("--disable-blink-features=AutomationControlled")
    opts.add_experimental_option("excludeSwitches", ["enable-automation"])
    opts.add_experimental_option("useAutomationExtension", False)
    # 用户数据目录 — 可复用已有登录态; 打包后需放 exe 同级以持久化
    profile_dir = os.path.join(
        os.path.dirname(sys.executable) if getattr(sys, "frozen", False) else os.path.dirname(os.path.abspath(__file__)),
        ".libseat_chrome_profile",
    )
    opts.add_argument(f"--user-data-dir={profile_dir}")

    # chromedriver 检测: 缺失时给出明确指引, 不触发 Selenium Manager 自动下载(国内网络会卡死)
    import shutil as _shutil
    cd_path = chromedriver_path or _shutil.which("chromedriver")
    if not cd_path:
        log.error("=" * 50)
        log.error("未找到 chromedriver!")
        log.error("Selenium Manager 自动下载已被禁用(国内网络易超时卡死)。")
        log.error("请手动安装 chromedriver:")
        log.error("  方法1 (推荐):  brew install --cask chromedriver")
        log.error("  方法2: 下载后放到 PATH, 或用环境变量指定:")
        log.error("          export LIBSEAT_CHROMEDRIVER=/path/to/chromedriver")
        log.error("  下载地址: https://googlechromelabs.github.io/chrome-for-testing/")
        log.error("  注意: 版本必须与 Chrome 主版本一致")
        log.error("=" * 50)
        sys.exit(1)

    service = Service(executable_path=cd_path)

    # 禁用 Selenium Manager (防止意外触发自动下载导致卡死)
    os.environ.setdefault("SE_MANAGER_ENABLED", "false")

    log.info(f"使用 chromedriver: {cd_path}")
    if progress_cb:
        progress_cb("login", f"正在启动浏览器 (chromedriver: {cd_path})")
    driver = webdriver.Chrome(service=service, options=opts)

    try:
        log.info(f"正在打开登录页面: {auth_url}")
        if progress_cb:
            progress_cb("login", "浏览器已打开, 正在跳转登录页...")
        driver.get(auth_url)

        log.info("=" * 50)
        log.info("请在浏览器中完成登录!")
        log.info("登录成功后脚本会自动继续...")
        log.info("=" * 50)
        if progress_cb:
            progress_cb("login", "请在弹出浏览器中完成登录 (最长等待 5 分钟)")

        # 等待用户登录 — 监测 URL 变化 (登录成功后会跳转)
        # 最长等待 5 分钟
        start_wait = time.time()
        max_wait = 300

        # 先等待离开登录页面
        while time.time() - start_wait < max_wait:
            if cancel_event is not None and cancel_event.is_set():
                log.info("登录已取消 (cancel_event)")
                if progress_cb:
                    progress_cb("error", "登录已取消")
                return {}, {}
            current_url = driver.current_url or ""
            if "authserver/login" not in current_url:
                break
            time.sleep(1)
        else:
            if cancel_event is not None and cancel_event.is_set():
                log.info("登录已取消 (cancel_event)")
                if progress_cb:
                    progress_cb("error", "登录已取消")
                return {}, {}
            log.warning("等待登录超时 (5分钟), 尝试继续...")

        # 如果还没到 libseat 域名, 主动导航过去获取 ic-cookie
        if "libseat.njfu.edu.cn" not in (driver.current_url or ""):
            log.info("导航到图书馆主页获取 ic-cookie ...")
            if progress_cb:
                progress_cb("login", "登录成功, 正在跳转图书馆主页...")
            driver.get(target_url)
            time.sleep(3)

        # 等页面加载
        time.sleep(2)

        # 提取所有 cookies
        if progress_cb:
            progress_cb("login", "正在提取 cookies 与用户信息...")
        cookies = {}
        for c in driver.get_cookies():
            cookies[c["name"]] = c["value"]

        log.info(f"成功获取 {len(cookies)} 个 cookies:")
        for name, value in cookies.items():
            masked = value[:8] + "..." if len(value) > 8 else value
            log.info(f"  {name} = {masked}")

        # 读取 sessionStorage 中的 userInfo (accNo 是预约接口的关键, token 是请求头必需)
        user_info = read_session_user(driver)
        if user_info:
            acc_no = user_info.get("accNo") or user_info.get("pid")
            log.info(f"✅ 已获取 userInfo: accNo={acc_no} token={str(user_info.get('token'))[:8]}...")
            if progress_cb:
                progress_cb("done", f"登录成功! 用户: {user_info.get('trueName', '')} accNo: {acc_no}")
        else:
            acc_no = None
            log.warning("⚠️ 未从 sessionStorage 获取到 userInfo, 预约提交可能被拒绝 (code 100)")
            if progress_cb:
                progress_cb("warn", "未获取到 userInfo, 预约提交可能被拒绝 (code 100)")

        return cookies, user_info

    finally:
        driver.quit()


def read_session_user(driver) -> dict:
    """从浏览器 sessionStorage 读取 userInfo (最长等待 20 秒)"""
    deadline = time.time() + 20
    last_raw = ""
    while time.time() < deadline:
        try:
            last_raw = driver.execute_script("return sessionStorage.getItem('userInfo')")
            if last_raw:
                info = json.loads(last_raw)
                if info.get("token"):
                    return info
        except Exception as exc:
            log.debug(f"读取 sessionStorage 异常: {exc}")
        time.sleep(1)
    if last_raw:
        log.debug(f"sessionStorage.userInfo = {last_raw[:300]}")
    return {}


def load_credentials(path: str) -> tuple[dict, str]:
    """从文件加载 (cookies, token)
    兼容旧格式 (纯 cookies dict) 与新格式 ({"cookies":..., "token":...})
    """
    data = json.loads(open(path).read())
    if isinstance(data, list):
        return {c["name"]: c["value"] for c in data}, {}
    if isinstance(data, dict) and "cookies" in data:
        return data["cookies"], data.get("user_info", {})
    return data, {}


def save_credentials(path: str, cookies: dict, user_info: dict = None) -> None:
    """保存 cookies + userInfo (含 accNo/token) 到文件"""
    os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
    with open(path, "w") as f:
        json.dump({"cookies": cookies, "user_info": user_info or {}}, f, indent=2)
    log.info(f"凭证已保存到 {path}")


def cookies_from_file(path: str) -> dict:
    """向后兼容: 从 JSON 文件加载 cookies"""
    cookies, _ = load_credentials(path)
    return cookies


# ============================================================
# API 客户端 (真实接口: /ic-web 前缀, 已从前端 JS 逆向确认)
# ============================================================

class LibSeatAPI:
    """图书馆座位系统 API 客户端
    接口基址: {api_base}/ic-web
    关键接口 (已逆向确认):
      GET  /ic-web/reserve          # 查询座位列表 (roomIds, resvDates, sysKind=8)
      POST /ic-web/reserve          # 预约提交
      GET  /ic-web/reserve/punishInfo  # 违约查询
    """

    def __init__(self, base_url: str, cookies: dict, timeout: int = 10, app_acc_no: str = "", token: str = ""):
        self.base = base_url.rstrip("/")
        self.timeout = timeout
        self.app_acc_no = app_acc_no
        self.token = token
        self.session = requests.Session()
        self.session.headers.update({
            "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) "
                          "AppleWebKit/537.36 (KHTML, like Gecko) "
                          "Chrome/152.0.0.0 Safari/537.36",
            "Accept": "application/json, text/plain, */*",
            "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8",
            "Referer": f"{self.base}/",
            "X-Requested-With": "XMLHttpRequest",
        })
        if token:
            self.session.headers["token"] = token
        if cookies:
            self.session.cookies.update(cookies)

    def _url(self, path: str) -> str:
        if path.startswith("http"):
            return path
        return f"{self.base}/{path.lstrip('/')}"

    def _get(self, path: str, params: dict = None) -> dict | None:
        try:
            resp = self.session.get(self._url(path), params=params, timeout=self.timeout)
            resp.raise_for_status()
            return resp.json()
        except requests.RequestException as e:
            log.error(f"GET {path} 失败: {e}")
            return None
        except json.JSONDecodeError:
            log.error(f"GET {path} 返回非 JSON: {resp.text[:200]}")
            return None

    def _post(self, path: str, params: dict = None, json_data: dict = None) -> dict | None:
        try:
            resp = self.session.post(
                self._url(path), params=params, json=json_data, timeout=self.timeout
            )
            resp.raise_for_status()
            return resp.json()
        except requests.RequestException as e:
            log.error(f"POST {path} 失败: {e}")
            return None
        except json.JSONDecodeError:
            log.error(f"POST {path} 返回非 JSON: {resp.text[:200]}")
            return None

    # ---- 业务接口 ----

    def get_seat_layout(self, room_id: str) -> dict | None:
        log.info(f"获取座位布局 room={room_id}")
        return self._get("openScope", {"roomId": room_id})

    def get_sys_info(self, room_id: str, sys_kind: int = 4, status: int = 2) -> dict | None:
        return self._get("sysInfo", {
            "sysType": 2,
            "sysValue": room_id,
            "sysKind": sys_kind,
            "status": status,
        })

    def get_reserve_list(self, room_ids: str, date: str, sys_kind: int = 8) -> dict | None:
        """查询座位列表 (GET /ic-web/reserve)"""
        log.info(f"查询座位列表 room={room_ids} date={date}")
        return self._get("reserve", {
            "roomIds": room_ids,
            "resvDates": date,
            "sysKind": sys_kind,
        })

    def resolve_dev_ids(self, room_id: str, date: str, seat_names: list[str]) -> list[str]:
        """将座位名 (如 7F-B075) 解析为 devId 列表
        通过查询接口获取座位列表, 匹配 devName 字段
        """
        result = self.get_reserve_list(room_id, date)
        if not result or result.get("code") not in (0, 200, "0", "200"):
            log.error(f"查询座位列表失败: {json.dumps(result, ensure_ascii=False)[:300]}")
            return seat_names  # 降级: 原样返回

        seats = result.get("data") or []
        name_to_id = {}
        for seat in seats:
            if isinstance(seat, dict):
                name = seat.get("devName") or seat.get("seatName") or seat.get("name")
                dev_id = seat.get("devId") or seat.get("id") or seat.get("seatId")
                if name and dev_id:
                    name_to_id[str(name)] = str(dev_id)

        resolved = []
        for name in seat_names:
            if name in name_to_id:
                resolved.append(name_to_id[name])
                log.info(f"  座位 {name} -> devId {name_to_id[name]}")
            else:
                log.warning(f"  座位 {name} 未找到对应 devId, 将原样使用")
                resolved.append(name)
        return resolved

    def check_alive(self) -> bool:
        """检查 cookies 是否有效 (通过违约接口探测)"""
        result = self._get("reserve/punishInfo")
        if result is None:
            return False
        code = result.get("code")
        # code=300 表示未登录/过期
        if code in (300, 301, 302, 401, 403):
            return False
        log.info(f"cookies 有效 (punishInfo code={code})")
        return True

    def reserve_seat(self, room_id: str, dev_id: str, date: str,
                     start_time: str, end_time: str,
                     test_name: str = "", captcha: str = "") -> dict | None:
        """预约座位 (POST /ic-web/reserve)
        参数 (已从前端 JS 逆向确认, 类型与系统严格一致):
          sysKind=8 (int), appAccNo (int), memberKind=1 (int),
          resvMember=[int], resvBeginTime='YYYY-MM-DD HH:mm:00' (横杠),
          resvEndTime='YYYY-MM-DD HH:mm:00', testName, captcha,
          resvProperty=0 (int), resvDev=[int], memo
        注意: 只允许预约今天/明天
        """
        if not self.app_acc_no:
            log.warning("未配置 appAccNo (一卡通号), 预约提交将缺少该参数")
            return None
        acc_no = int(self.app_acc_no)
        dev_id_int = int(dev_id)
        begin = f"{date[:4]}-{date[4:6]}-{date[6:]} {start_time}:00"
        end = f"{date[:4]}-{date[4:6]}-{date[6:]} {end_time}:00"

        payload = {
            "sysKind": 8,
            "appAccNo": acc_no,
            "memberKind": 1,
            "resvMember": [acc_no],
            "resvBeginTime": begin,
            "resvEndTime": end,
            "testName": test_name,
            "captcha": captcha,
            "resvProperty": 0,
            "resvDev": [dev_id_int],
            "memo": "",
        }
        log.info(f"POST /ic-web/reserve dev={dev_id_int} date={date} {start_time}-{end_time}")
        log.debug(f"  body: {json.dumps(payload, ensure_ascii=False)}")
        return self._post("reserve", json_data=payload)

    def get_punish_info(self) -> dict | None:
        return self._get("reserve/punishInfo")

    def get_all_codes(self, code_type: int) -> dict | None:
        return self._get("codingTable/getAll", {"codeType": code_type})

    def get_temp_leave(self, room_id: str) -> dict | None:
        return self._get("tempLeave", {"roomId": room_id})

    def test_connection(self) -> bool:
        result = self.get_punish_info()
        return result is not None


# ============================================================
# 交互式座位选择
# ============================================================

def interactive_seat_select(api: LibSeatAPI, room_id: str,
                            date: str, keyword: str = "") -> list[dict]:
    """
    交互式选择座位, 返回选中的座位列表
    """
    log.info("正在获取座位信息...")

    # 方法1: 通过 openScope 获取布局
    layout = api.get_seat_layout(room_id)

    # 方法2: 通过 reserve 接口获取已有预约 (反推可用)
    reserve_info = api.get_reserve_list(room_id, date)

    # 方法3: sysInfo 获取座位列表
    sys_info = api.get_sys_info(room_id, sys_kind=4, status=2)

    log.info("\n--- API 返回数据 (供参考) ---")
    if layout:
        log.info(f"  openScope 返回: {json.dumps(layout, ensure_ascii=False)[:500]}")
    if reserve_info:
        log.info(f"  reserve 返回:   {json.dumps(reserve_info, ensure_ascii=False)[:500]}")
    if sys_info:
        log.info(f"  sysInfo 返回:   {json.dumps(sys_info, ensure_ascii=False)[:500]}")
    log.info("--- 结束 ---\n")

    # 尝试从各种响应中提取座位列表
    seats = []

    # 从 openScope 提取 (常见结构: data -> layout -> zones -> seats)
    if layout and isinstance(layout, dict):
        # 尝试不同层级
        for key_path in [["data"], ["data", "layout"], ["data", "zones"]]:
            obj = layout
            for k in key_path:
                obj = obj.get(k, {}) if isinstance(obj, dict) else {}
            if isinstance(obj, list) and len(obj) > 0:
                seats = obj
                break
            elif isinstance(obj, dict):
                # 可能是 {zoneId: [seats]} 格式
                for v in obj.values():
                    if isinstance(v, list) and len(v) > 0:
                        seats = v
                        break
                if seats:
                    break

    # 从 sysInfo 提取
    if not seats and sys_info and isinstance(sys_info, dict):
        data = sys_info.get("data", sys_info)
        if isinstance(data, list):
            seats = data
        elif isinstance(data, dict):
            for v in data.values():
                if isinstance(v, list):
                    seats = v
                    break

    # 座位关键词过滤
    if seats and keyword:
        filtered = []
        for s in seats:
            name = ""
            if isinstance(s, dict):
                name = str(s.get("seatName", "")) + str(s.get("name", "")) + str(s.get("seatNum", ""))
            elif isinstance(s, str):
                name = s
            if keyword in name:
                filtered.append(s)
        if filtered:
            log.info(f"关键词 '{keyword}' 过滤: {len(seats)} -> {len(filtered)} 个座位")
            seats = filtered

    if not seats:
        log.warning("未能自动解析座位列表, 请手动输入座位ID")
        manual = input("输入座位ID (逗号分隔, 直接回车跳过): ").strip()
        if manual:
            return [{"seatId": s.strip(), "seatName": s.strip()} for s in manual.split(",")]
        return []

    # 显示座位列表
    print(f"\n{'='*60}")
    print(f"  找到 {len(seats)} 个座位")
    print(f"{'='*60}")

    for i, seat in enumerate(seats):
        if isinstance(seat, dict):
            seat_id = seat.get("seatId", seat.get("id", seat.get("seatNum", "?")))
            seat_name = seat.get("seatName", seat.get("name", seat.get("seatNum", str(seat_id))))
            status = seat.get("status", "")
            print(f"  [{i+1:3d}] {seat_name} (ID: {seat_id}) {status}")
        else:
            print(f"  [{i+1:3d}] {seat}")

    print(f"{'='*60}")
    print("  输入序号选择 (逗号分隔), 输入 'all' 选择全部, 直接回车取消")
    choice = input("  选择: ").strip()

    if not choice:
        return []
    if choice.lower() == "all":
        return seats

    selected = []
    for idx_str in choice.split(","):
        try:
            idx = int(idx_str.strip()) - 1
            if 0 <= idx < len(seats):
                selected.append(seats[idx])
        except ValueError:
            pass

    return selected


# ============================================================
# 轮询抢座核心逻辑
# ============================================================

def wait_until(hour: int, minute: int, second: int = 0):
    """阻塞等待到指定时刻"""
    now = datetime.now()
    target = now.replace(hour=hour, minute=minute, second=second, microsecond=0)
    if target <= now:
        # 如果目标时间已过, 不等待 (可能是用于调试)
        log.info(f"目标时间 {target.strftime('%H:%M:%S')} 已过, 立即开始")
        return

    diff = (target - now).total_seconds()
    log.info(f"等待到 {target.strftime('%H:%M:%S')} (还剩 {diff:.1f} 秒)")

    # 粗等待: 每30秒打印一次
    while True:
        remaining = (target - datetime.now()).total_seconds()
        if remaining <= 30:
            break
        time.sleep(min(remaining - 25, 30))
        log.info(f"  倒计时 {remaining:.0f} 秒 ...")

    # 精细等待: 最后30秒用 busy-wait 提高精度
    log.info("进入精确等待模式...")
    while datetime.now() < target:
        remaining = (target - datetime.now()).total_seconds()
        if remaining > 1:
            time.sleep(0.01)  # 10ms 精度
        elif remaining > 0.05:
            time.sleep(0.001)  # 1ms 精度
        # 最后50ms: busy spin
        else:
            pass  # busy loop for max precision

    elapsed = (datetime.now() - target).total_seconds()
    log.info(f"到达目标时间! (偏差: {elapsed*1000:+.1f}ms)")


def compute_time_range(booking_time: str, duration_min: int) -> tuple[str, str]:
    """计算入座时间和离开时间"""
    h, m = map(int, booking_time.split(":"))
    start_dt = datetime(2026, 1, 1, h, m)
    end_dt = start_dt + timedelta(minutes=duration_min)
    return start_dt.strftime("%H:%M"), end_dt.strftime("%H:%M")


def polling_reserve(
    api: LibSeatAPI,
    room_id: str,
    seat_ids: list[str],
    date: str,
    start_time: str,
    end_time: str,
    interval: float = 0.3,
    max_retry: int = 3,
    stop_event=None,
) -> bool:
    """
    轮询抢座主循环
    返回 True 表示成功
    stop_event: threading.Event, 设置后停止轮询
    """
    attempt = 0
    results = []

    log.info(f"\n{'🚀'*20}")
    log.info(f"开始抢座!")
    log.info(f"  房间: {room_id}")
    log.info(f"  座位: {', '.join(seat_ids)}")
    log.info(f"  日期: {date}")
    log.info(f"  时间: {start_time} - {end_time}")
    log.info(f"  间隔: {interval}秒")
    log.info(f"{'🚀'*20}\n")

    while True:
        if stop_event is not None and stop_event.is_set():
            log.info("收到停止信号, 结束轮询")
            log.info(f"成功预约 {len(results)}/{len(seat_ids)} 个座位")
            return bool(results)

        attempt += 1
        now_str = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        log.info(f"[#{attempt}] {now_str} 尝试预约...")

        for seat_id in seat_ids:
            result = api.reserve_seat(room_id, seat_id, date, start_time, end_time)
            ts = datetime.now().strftime("%H:%M:%S.%f")[:-3]

            if result is None:
                log.warning(f"  {ts} seat={seat_id}: 请求失败")
                continue

            # 判断是否成功 — 根据实际API响应格式调整
            success = False
            msg = ""

            if isinstance(result, dict):
                code = result.get("code", result.get("status", result.get("ret", -1)))
                msg = result.get("msg", result.get("message", result.get("info", "")))
                data = result.get("data", None)

                # 常见成功 code: 0, 200, "0", "success"
                if code in (0, 200, "0", "200", "success", True):
                    success = True
                elif isinstance(code, str) and "success" in code.lower():
                    success = True
                # 如果 data 非空且没有错误
                elif data and not msg:
                    success = True

            log.info(f"  {ts} seat={seat_id}: {'✅ 成功!' if success else '❌ ' + str(msg) if msg else '❌ 失败'}")
            log.info(f"           原始响应: {json.dumps(result, ensure_ascii=False)[:300]}")

            if success:
                log.info(f"\n{'🎉'*20}")
                log.info(f"预约成功! seat={seat_id}")
                log.info(f"{'🎉'*20}")
                results.append(seat_id)
                if len(results) >= len(seat_ids):
                    return True
                # 还有其他座位没抢到, 继续

        # 判断是否已达最大重试
        if attempt >= max_retry and max_retry > 0:
            log.info(f"\n已达到最大重试次数 ({max_retry})")
            if results:
                log.info(f"成功预约 {len(results)}/{len(seat_ids)} 个座位")
                return True
            return False

        time.sleep(interval)


# ============================================================
# 主流程
# ============================================================

def main():
    parser = argparse.ArgumentParser(description="南京林业大学图书馆座位预约脚本")
    parser.add_argument("--config", action="store_true", help="修改配置")
    parser.add_argument("--show-cookies", action="store_true", help="仅登录获取cookies (调试)")
    parser.add_argument("--cookies-file", type=str, help="从JSON文件加载cookies (跳过浏览器登录)")
    parser.add_argument("--save-cookies", type=str, help="保存cookies到JSON文件")
    parser.add_argument("--no-wait", action="store_true", help="不等待定时, 立即开始轮询")
    parser.add_argument("--dry-run", action="store_true", help="仅查询, 不实际预约")
    parser.add_argument("--test-far-date", action="store_true", help="使用30天后的日期测试 (安全)")
    args = parser.parse_args()

    # ---- 配置修改模式 ----
    if args.config:
        from config import edit_config
        edit_config()
        return

    # ---- 加载配置 ----
    from config import Config
    cfg = Config.load()

    # --test-far-date: 使用30天后的日期
    if args.test_far_date:
        far_date = (datetime.now() + timedelta(days=30)).strftime("%Y%m%d")
        cfg.date = far_date
        log.info(f"测试模式: 使用日期 {far_date}")

    # ---- 登录 / 加载凭证 (cookies + userInfo) ----
    cookies = None
    user_info = {}
    cookies_path = args.cookies_file or cfg.cookies_file

    # 1. 优先尝试从文件加载并检查
    file_cookies, file_user = {}, {}
    if cookies_path and os.path.exists(cookies_path):
        log.info(f"发现本地凭证文件: {cookies_path}")
        file_cookies, file_user = load_credentials(cookies_path)
    elif cookies_path:
        log.info(f"凭证文件不存在: {cookies_path}")

    # 完整性检查: 缺 cookies 或缺 userInfo(含 token/accNo)
    missing = []
    if not file_cookies:
        missing.append("cookies")
    if not file_user or not file_user.get("token"):
        missing.append("token")
    file_acc = file_user.get("accNo") if file_user else None

    if file_cookies and not missing:
        # 2. cookies+token 齐全, 探测有效性
        api_probe = LibSeatAPI(cfg.api_base, file_cookies, timeout=cfg.timeout,
                               app_acc_no=file_acc, token=file_user.get("token", ""))
        if api_probe.check_alive():
            log.info("✅ 本地凭证完整且有效, 跳过浏览器登录")
            if cfg.app_acc_no and str(cfg.app_acc_no) != str(file_acc):
                log.info(f"使用登录获取的 accNo={file_acc} (覆盖配置中的 {cfg.app_acc_no})")
            cfg.app_acc_no = str(file_acc)
            cookies, user_info = file_cookies, file_user
        else:
            log.warning("⚠️ 本地凭证已过期 (服务器校验失败)")
            missing.append("已过期")
    else:
        if missing:
            log.warning(f"⚠️ 本地凭证不完整: 缺少 {', '.join(missing)}")

    # 3. 不完整或过期 -> 询问用户是否重新登录
    if cookies is None:
        if args.cookies_file:
            log.error(f"指定文件 {args.cookies_file} 中的凭证不可用")
        print("\n" + "=" * 50)
        print("  检测到凭证不可用, 需要处理")
        print("=" * 50)
        choice = input("是否重新登录?(浏览器弹出后手动登录) [y/N]: ").strip().lower()
        if choice == "y":
            cookies, user_info = browser_login(
                auth_url=cfg.auth_url,
                target_url=f"{cfg.api_base.split('/ic-web')[0]}/",
                chromedriver_path=cfg.chromedriver,
            )
            if user_info and user_info.get("accNo"):
                cfg.app_acc_no = str(user_info["accNo"])
        else:
            log.warning("用户选择不重新登录")
            retry_old = input("是否使用现有(可能失效的)凭证继续? [y/N]: ").strip().lower()
            if retry_old == "y" and file_cookies:
                cookies, user_info = file_cookies, file_user
                log.warning("将使用现有凭证继续, 预约可能失败 (如返回 code 100)")
            else:
                print("已退出, 请重新运行脚本。")
                sys.exit(1)

    if not cookies:
        log.error("未获取到 cookies, 退出")
        sys.exit(1)

    # 3. 登录成功则自动保存 (供下次复用)
    save_credentials(cookies_path, cookies, user_info)

    # ---- 仅显示 cookies ----
    if args.show_cookies:
        print(json.dumps(cookies, indent=2))
        return

    # ---- 创建 API 客户端 ----
    acc_no = user_info.get("accNo") or cfg.app_acc_no
    token = (user_info.get("token") or "") if user_info else ""
    api = LibSeatAPI(cfg.api_base, cookies, timeout=cfg.timeout, app_acc_no=acc_no, token=token)

    # 测试连接
    log.info("测试 API 连接...")
    if not api.test_connection():
        log.warning("API 连接测试失败, 可能 cookies 已失效")
        retry = input("是否继续? (y/N): ").strip().lower()
        if retry != "y":
            sys.exit(1)
    else:
        log.info("API 连接正常 ✓")

    # 查询违约信息
    punish = api.get_punish_info()
    if punish:
        log.info(f"违约信息: {json.dumps(punish, ensure_ascii=False)[:300]}")

    # ---- 选择座位 ----
    if not cfg.app_acc_no:
        log.warning("未配置一卡通号 (LIBSEAT_APP_ACC_NO), 预约提交可能失败")
        print("提示: 预约需要一卡通号, 请运行 python reserve.py --config 设置")

    seat_ids = list(cfg.seat_ids)

    if not seat_ids:
        log.info("未预设座位, 进入交互选择...")
        selected = interactive_seat_select(api, cfg.room_id, cfg.date, cfg.seat_keyword)
        for s in selected:
            sid = s.get("devId", s.get("seatId", s.get("id", s.get("seatNum", "")))) if isinstance(s, dict) else str(s)
            if sid:
                seat_ids.append(str(sid))

        if not seat_ids:
            log.error("未选择任何座位")
            sys.exit(1)
    else:
        # 配置的是座位名 (如 7F-B075), 解析为 devId
        log.info("解析座位名 -> devId ...")
        seat_ids = api.resolve_dev_ids(cfg.room_id, cfg.date, seat_ids)

    # 计算时间范围
    start_time, end_time = compute_time_range(cfg.booking_time, cfg.booking_duration)

    # ---- 打印最终计划 ----
    cfg.seat_ids = seat_ids
    cfg.print_current()
    print(f"  入座时间范围: {start_time} - {end_time}")

    if args.dry_run:
        log.info("Dry-run 模式, 仅查询不预约")
        result = api.get_reserve_list(cfg.room_id, cfg.date)
        print(f"当前座位列表: {json.dumps(result, ensure_ascii=False)[:1000]}")
        return

    # ---- 确认开始 ----
    confirm = input("\n确认开始抢座? (y/N): ").strip().lower()
    if confirm != "y":
        log.info("已取消")
        return

    # ---- 等待 / 立即开始 ----
    if not args.no_wait and not cfg.start_now:
        wait_until(cfg.start_hour, cfg.start_minute)
    elif cfg.start_now:
        log.info("已设置 start_now, 立即开始轮询")

    # ---- 开始轮询 ----
    success = polling_reserve(
        api=api,
        room_id=cfg.room_id,
        seat_ids=seat_ids,
        date=cfg.date,
        start_time=start_time,
        end_time=end_time,
        interval=cfg.poll_interval,
        max_retry=cfg.max_retry,
    )

    if success:
        print("\n" + "=" * 50)
        print("  🎉 预约成功! 请按时到达图书馆入座。")
        print("  ⚠️  如无法到场请提前取消, 避免违约。")
        print("=" * 50)
    else:
        print("\n" + "=" * 50)
        print("  😞 预约未成功, 请稍后重试。")
        print("=" * 50)


if __name__ == "__main__":
    main()
