#!/usr/bin/env python3
"""
图书馆座位预约脚本配置模块
所有配置项均支持环境变量覆盖
"""
import os
import sys
import json
from pathlib import Path
from dataclasses import dataclass, field, asdict
from typing import Optional

# PyInstaller 打包后 __file__ 指向临时解压目录, 配置文件需放在 exe 同目录
_CONFIG_DIR = Path(sys.executable).parent if getattr(sys, "frozen", False) else Path(__file__).parent
CONFIG_FILE = _CONFIG_DIR / ".libseat_config.json"

# ============================================================
# 环境变量名定义
# ============================================================
ENV_KEYS = {
    "room_id":          "LIBSEAT_ROOM_ID",
    "date":             "LIBSEAT_DATE",              # YYYYMMDD
    "seat_ids":         "LIBSEAT_SEAT_IDS",          # 逗号分隔的座位号
    "poll_interval":    "LIBSEAT_POLL_INTERVAL",     # 轮询间隔(秒)
    "start_now":        "LIBSEAT_START_NOW",         # 立即开始轮询 (true/false)
    "start_hour":       "LIBSEAT_START_HOUR",        # 开始轮询的小时 (24h)
    "start_minute":     "LIBSEAT_START_MINUTE",      # 开始轮询的分钟
    "api_base":         "LIBSEAT_API_BASE",
    "auth_url":         "LIBSEAT_AUTH_URL",
    "cookies_file":     "LIBSEAT_COOKIES_FILE",   # cookies 持久化路径
    "app_acc_no":       "LIBSEAT_APP_ACC_NO",       # 一卡通号 (预约提交必填)
    "chromedriver":     "LIBSEAT_CHROMEDRIVER",      # chromedriver 路径, 空则自动查找
    "headless":         "LIBSEAT_HEADLESS",          # 是否无头模式 (登录时强制 False)
    "timeout":          "LIBSEAT_TIMEOUT",           # 请求超时(秒)
    "max_retry":        "LIBSEAT_MAX_RETRY",         # 单次预约最大重试
    "booking_time":     "LIBSEAT_BOOKING_TIME",      # 预约起始时间 HH:MM
    "booking_duration": "LIBSEAT_BOOKING_DURATION",  # 预约时长(分钟)
    "seat_keyword":     "LIBSEAT_SEAT_KEYWORD",      # 座位关键词过滤
}


@dataclass
class Config:
    """预约配置"""
    # ---- 基本信息 ----
    room_id: str = "111488396"
    date: str = ""                          # YYYYMMDD, 空则自动取明天
    seat_ids: list[str] = field(default_factory=list)

    # ---- 轮询 ----
    poll_interval: float = 0.3              # 秒
    start_now: bool = False                 # True 则立即开始轮询
    start_hour: int = 22                    # 22:00 开始抢
    start_minute: int = 0

    # ---- API ----
    api_base: str = "https://libseat.njfu.edu.cn/ic-web"
    auth_url: str = "https://uia.njfu.edu.cn/authserver/login"
    cookies_file: str = str(CONFIG_FILE.parent / ".libseat_credentials.json")
    app_acc_no: str = ""                    # 一卡通号
    timeout: int = 10
    max_retry: int = 3

    # ---- 浏览器 ----
    chromedriver: str = ""
    headless: str = "false"

    # ---- 预约细节 ----
    booking_time: str = "08:00"             # 入座时间 HH:MM
    booking_duration: int = 300             # 5小时 = 300分钟
    seat_keyword: str = ""                  # 座位名称关键词过滤

    # ---- 运行时 (不持久化) ----
    cookies: dict = field(default_factory=dict)
    browser_profile: str = ""               # Chrome 用户数据目录

    def save(self):
        """保存配置到文件"""
        data = asdict(self)
        data.pop("cookies", None)
        CONFIG_FILE.write_text(json.dumps(data, ensure_ascii=False, indent=2))
        print(f"[✓] 配置已保存到 {CONFIG_FILE}")

    @classmethod
    def load(cls) -> "Config":
        """加载配置: 环境变量 > 配置文件 > 默认值"""
        cfg = cls()

        # 1. 从文件加载
        if CONFIG_FILE.exists():
            try:
                data = json.loads(CONFIG_FILE.read_text())
                for k, v in data.items():
                    if hasattr(cfg, k):
                        setattr(cfg, k, v)
            except Exception:
                pass

        # 2. 环境变量覆盖
        env_map = {
            "room_id":          (str,  None),
            "date":             (str,  None),
            "seat_ids":         (None, None),   # 特殊处理
            "poll_interval":    (float, None),
            "start_now":        (None, None),   # 特殊处理: 布尔
            "start_hour":       (int,   None),
            "start_minute":     (int,   None),
            "api_base":         (str,  None),
            "auth_url":         (str,  None),
            "cookies_file":     (str,  None),
            "app_acc_no":       (str,  None),
            "chromedriver":     (str,  None),
            "headless":         (str,  None),
            "timeout":          (int,   None),
            "max_retry":        (int,   None),
            "booking_time":     (str,  None),
            "booking_duration": (int,   None),
            "seat_keyword":     (str,  None),
        }

        for attr, (typ, _) in env_map.items():
            env_key = ENV_KEYS[attr]
            val = os.environ.get(env_key)
            if val is not None:
                if attr == "seat_ids":
                    setattr(cfg, attr, [s.strip() for s in val.split(",") if s.strip()])
                elif attr == "start_now":
                    setattr(cfg, attr, val.strip().lower() in ("1", "true", "yes", "y", "on"))
                elif typ is not None:
                    setattr(cfg, attr, typ(val))

        # 3. 自动计算日期 (如果未指定)
        if not cfg.date:
            from datetime import datetime, timedelta
            tomorrow = datetime.now() + timedelta(days=1)
            cfg.date = tomorrow.strftime("%Y%m%d")

        return cfg

    def print_current(self):
        """打印当前配置"""
        print("\n" + "=" * 50)
        print("📋 当前预约配置")
        print("=" * 50)
        print(f"  房间ID:       {self.room_id}")
        print(f"  预约日期:     {self.date}")
        print(f"  目标座位:     {', '.join(self.seat_ids) if self.seat_ids else '(未设置, 将选择所有可用)'}")
        print(f"  入座时间:     {self.booking_time}")
        print(f"  预约时长:     {self.booking_duration}分钟")
        print(f"  轮询开始:     {'立即开始' if self.start_now else f'{self.start_hour:02d}:{self.start_minute:02d}'}")
        print(f"  轮询间隔:     {self.poll_interval}秒")
        print(f"  最大重试:     {self.max_retry}")
        print(f"  API地址:      {self.api_base}")
        print(f"  座位关键词:   {self.seat_keyword or '(无过滤)'}")
        print(f"  一卡通号:     {self.app_acc_no or '(未设置)'}")
        print(f"  Cookies文件:  {self.cookies_file}")
        print("=" * 50 + "\n")


ROOMS = [
    ("二层A区", "100455344"),
    ("二层B区", "100455346"),
    ("三层A区", "100455350"),
    ("三层B区", "100455352"),
    ("三层C区", "100455354"),
    ("三层夹层", "111488386"),
    ("四层A区", "100455356"),
    ("四层夹层", "111488388"),
    ("五层A区", "100455358"),
    ("六层A区", "100455360"),
    ("七层北侧", "106658017"),
    ("七层南侧", "111488396"),
]


def edit_config():
    """交互式修改配置"""
    cfg = Config.load()
    cfg.print_current()

    # 房间选择: 支持输入序号 (如 12) 或房间ID (如 111488396), 回车保留
    print("=" * 50)
    print("  选择房间")
    print("=" * 50)
    for i, (name, rid) in enumerate(ROOMS, 1):
        mark = "  ← 当前" if str(rid) == str(cfg.room_id) else ""
        print(f"    {i}. {name} ({rid}){mark}")
    choice = input(f"  输入序号 (1-{len(ROOMS)}) 或房间ID, 回车保留当前: ").strip()
    if choice:
        if choice.isdigit() and 1 <= int(choice) <= len(ROOMS):
            cfg.room_id = ROOMS[int(choice) - 1][1]
        elif any(choice == rid for _, rid in ROOMS):
            cfg.room_id = choice
        else:
            print("    无效输入, 保留当前房间")

    print("\n输入要修改的字段 (直接回车跳过):")
    print("-" * 40)

    fields_to_edit = [
        ("date",             "预约日期 (YYYYMMDD)", str),
        ("seat_ids",         "座位号 (逗号分隔)",   "list"),
        ("booking_time",     "入座时间 (HH:MM)",    str),
        ("booking_duration", "预约时长 (分钟)",      int),
        ("start_now",        "立即开始轮询 (true/false)", "bool"),
        ("start_hour",       "轮询开始小时 (0-23)",  int),
        ("start_minute",     "轮询开始分钟 (0-59)",  int),
        ("poll_interval",    "轮询间隔 (秒)",        float),
        ("max_retry",        "最大重试次数",         int),
        ("seat_keyword",     "座位关键词过滤",       str),
        ("app_acc_no",       "一卡通号",             str),
    ]

    for attr, label, typ in fields_to_edit:
        current = getattr(cfg, attr)
        if typ == "list":
            display = ", ".join(current) if current else "(空)"
        elif typ == "bool":
            display = "是" if current else "否"
        else:
            display = current
        val = input(f"  {label} [{display}]: ").strip()
        if val == "":
            continue
        if typ == "list":
            setattr(cfg, attr, [s.strip() for s in val.split(",") if s.strip()])
        elif typ == "bool":
            setattr(cfg, attr, val.strip().lower() in ("1", "true", "yes", "y", "on"))
        else:
            setattr(cfg, attr, typ(val))

    cfg.save()
    cfg.print_current()


if __name__ == "__main__":
    edit_config()
