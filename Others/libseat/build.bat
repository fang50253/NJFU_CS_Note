@echo off
chcp 65001 >nul
REM ============================================
REM 图书馆座位预约 - Windows 打包脚本
REM 需先安装: pip install pyinstaller
REM ============================================
cd /d %~dp0

echo [1/3] 安装依赖...
pip install -r requirements.txt pyinstaller
if errorlevel 1 goto :error

echo [2/3] 清理旧构建...
rmdir /s /q build dist 2>nul

echo [3/3] 开始打包...
pyinstaller --noconfirm --onefile --name 图书馆座位预约 --add-data "static;static" server.py
if errorlevel 1 goto :error

echo.
echo 打包完成: dist\图书馆座位预约.exe
echo 将 dist\图书馆座位预约.exe 复制到任意目录运行即可
echo 首次使用请自行安装 Chrome 并把 chromedriver.exe 加入 PATH
goto :eof

:error
echo.
echo 打包失败, 请检查上方错误信息
exit /b 1