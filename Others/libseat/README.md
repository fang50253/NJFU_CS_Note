# 南京林业大学图书馆座位预约脚本

自动预约图书馆座位，支持轮询抢座。提供两种使用方式：
- **CLI 脚本**（`reserve.py`）：交互式命令行
- **Web 服务器**（`server.py`）：浏览器页面操作，登录自动抓取凭证

## 安装

```bash
pip install -r requirements.txt
```

需要安装 Chrome 浏览器和对应版本的 [chromedriver](https://googlechromelabs.github.io/chrome-for-testing/)（放入 PATH 或设置 `LIBSEAT_CHROMEDRIVER` 环境变量）。

## Web 服务器使用

```bash
python server.py                # 默认从 8000 端口启动
python server.py --port 9000    # 从 9000 端口起
python server.py --host 0.0.0.0 # 允许局域网访问
```

> 端口被占用时自动递增寻找空闲端口（8000 → 8001 → ...）。

启动后浏览器访问 `http://127.0.0.1:8000/`（实际端口以启动日志为准）：

1. **登录** - 点击「浏览器登录」，服务端弹出浏览器窗口，手动登录后**自动抓取并保存 cookies/token**，无需手动复制
2. **配置** - 选择阅览室、日期、入座时间、时长、轮询间隔
3. **查座** - 点击「查询座位」加载座位网格，点击选择目标座位
4. **抢座** - 点击「开始预约」后台轮询，页面实时显示日志与结果

### API 接口

| 方法 | 路径 | 说明 |
|------|------|------|
| GET | `/api/status` | 凭证/登录/轮询状态 |
| POST | `/api/login` | 触发浏览器登录（异步弹窗） |
| GET | `/api/login/status` | 登录进度（stage: login/done/warn/error） |
| POST | `/api/login/cancel` | 取消登录 |
| GET | `/api/rooms` | 房间列表 |
| GET | `/api/config` | 当前配置 |
| POST | `/api/config` | 保存配置 |
| GET | `/api/seats?room_id=&date=` | 查询座位列表 |
| POST | `/api/reserve/start` | 启动轮询预约（异步） |
| POST | `/api/reserve/stop` | 停止轮询 |
| GET | `/api/reserve/status` | 轮询状态 |
| GET | `/api/logs?after=&n=` | 拉取日志 |

## CLI 使用

```bash
# 正常流程: 弹浏览器登录 -> 选座位 -> 22:00 开始抢
python reserve.py

# 修改配置 (含房间菜单选择)
python reserve.py --config

# 测试模式: 预约 30 天后的日期 (不产生违约)
python reserve.py --test-far-date

# 跳过等待立即轮询 (调试用)
python reserve.py --no-wait

# 仅登录获取 cookies (调试)
python reserve.py --show-cookies

# 从已保存的 cookies 文件启动 (免登录)
python reserve.py --cookies-file cookies.json

# 登录后保存 cookies 到文件
python reserve.py --save-cookies cookies.json

# 仅查询不预约
python reserve.py --dry-run
```

## 流程

1. **登录** - Selenium 弹出浏览器，访问 `uia.njfu.edu.cn/authserver/login`，手动登录后自动提取 cookies
2. **选座** - 脚本尝试从 `openScope` / `sysInfo` / `reserve` 接口拉取座位列表，交互式选择
3. **等待** - 默认等到 22:00（放座时间）开始轮询；设置 `LIBSEAT_START_NOW=true` 则立即开始
4. **抢座** - 按配置间隔轮询 `reserve` 接口，自动尝试多种参数格式

> ⚠️ **测试请使用 `--test-far-date`** 预约 30 天后的座位，避免违约。

## 环境变量

所有配置项均可用环境变量控制，优先级：**环境变量 > 配置文件 > 默认值**。

| 变量 | 说明 | 默认值 |
|------|------|--------|
| `LIBSEAT_ROOM_ID` | 房间 ID | `111488396` (七楼南侧) |
| `LIBSEAT_DATE` | 预约日期 YYYYMMDD | 自动取明天 |
| `LIBSEAT_SEAT_IDS` | 座位号列表（逗号分隔） | 空（交互选择） |
| `LIBSEAT_POLL_INTERVAL` | 轮询间隔（秒） | `0.3` |
| `LIBSEAT_START_NOW` | 立即开始轮询（true/false） | `false` |
| `LIBSEAT_START_HOUR` | 开始抢座小时 (0-23) | `22` |
| `LIBSEAT_START_MINUTE` | 开始抢座分钟 | `0` |
| `LIBSEAT_BOOKING_TIME` | 入座时间 HH:MM | `08:00` |
| `LIBSEAT_BOOKING_DURATION` | 预约时长（分钟） | `300` (5小时) |
| `LIBSEAT_SEAT_KEYWORD` | 座位关键词过滤 | 空 |
| `LIBSEAT_API_BASE` | API 基址 | `https://libseat.njfu.edu.cn` |
| `LIBSEAT_AUTH_URL` | 认证 URL | `https://uia.njfu.edu.cn/authserver/login` |
| `LIBSEAT_TIMEOUT` | 请求超时（秒） | `10` |
| `LIBSEAT_MAX_RETRY` | 最大重试次数 | `3` |
| `LIBSEAT_CHROMEDRIVER` | chromedriver 路径 | 自动查找 |
| `LIBSEAT_HEADLESS` | 无头模式 (登录除外) | `false` |

示例：

```bash
LIBSEAT_ROOM_ID=111488396 \
LIBSEAT_SEAT_IDS=111488400,111488401 \
LIBSEAT_POLL_INTERVAL=0.5 \
LIBSEAT_BOOKING_TIME=08:00 \
LIBSEAT_BOOKING_DURATION=240 \
python reserve.py
```

立即开始轮询（等价于 `--no-wait`，可通过配置/环境变量控制）：

```bash
LIBSEAT_START_NOW=true python reserve.py
```

## Windows 打包 exe

在 **Windows** 上执行（需先装 Python + Chrome + [chromedriver](https://googlechromelabs.github.io/chrome-for-testing/)）：

```bat
build.bat
```

- 产物：`dist\图书馆座位预约.exe`，复制到任意目录双击运行
- 三个源文件（`config.py` / `reserve.py` / `server.py`）均已做 PyInstaller 兼容：
  - 配置/凭证/浏览器 profile 自动保存在 **exe 同目录**（不会写入临时解压目录）
  - 前端页面 `static/` 通过 `--add-data "static;static"` 打进 exe
- Windows 需自行准备 Chrome 与匹配版本的 chromedriver.exe（放入 PATH 或用 `LIBSEAT_CHROMEDRIVER` 指定）

也可以用 PyInstaller 手动打包（macOS/Linux 同理，`--add-data` 分隔符用 `:`）：

```bash
pyinstaller --onefile --name 图书馆座位预约 --add-data "static:static" server.py
```

## 自定义

运行 `python reserve.py --config` 交互式修改配置，保存到 `.libseat_config.json`。

## 座位信息 API

已实现的查询接口（用于调试/选座）：

| 接口 | 用途 |
|------|------|
| `openScope?roomId=...` | 座位布局 |
| `sysInfo?sysType=2&sysValue=...&sysKind=4&status=2` | 座位状态 |
| `reserve?roomIds=...&resvDates=...&sysKind=8` | 查询预约记录 |
| `getAll?codeType=1010/1005` | 时段/时长代码表 |
| `punishInfo` | 违约记录 |
| `tempLeave?roomId=...` | 临时离座信息 |

## 注意

- 22:00 开抢（图书馆放座时间）
- 违约会被图书馆记录处罚，**测试务必用远期日期**
- 预约成功后请按时入座，无法到场请提前取消