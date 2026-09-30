"""
运行shell命令
"""

# import subprocess
# from utils.logger import logger


# def run_command(cmd):
#     """
#     执行shell命令
#     """

#     logger.info(f"Running: {cmd}")

#     process = subprocess.run(
#         cmd,
#         shell=True,
#         stdout=subprocess.PIPE,
#         stderr=subprocess.PIPE,
#         text=True,
#         errors='ignore'
#     )

#     if process.returncode != 0:
#         logger.error(process.stderr)
#         raise RuntimeError("Command failed")

#     logger.info(process.stdout)

#     return process.stdout

import subprocess
import sys

def run_command(cmd, check=True, capture=False):
    """运行 shell 命令并等待完成"""
    print(f"Running: {cmd.strip()}")
    sys.stdout.flush()
    
    # 使用 run() 会等待进程完成
    result = subprocess.run(
        cmd,
        shell=True,
        executable='/bin/bash',  # 使用 bash
        stdout=subprocess.PIPE if capture else None,
        stderr=subprocess.PIPE if capture else None,
        text=True
    )
    
    if check and result.returncode != 0:
        print(f"Command failed with exit code {result.returncode}")
        if capture:
            print(f"STDERR: {result.stderr}")
        raise RuntimeError(f"Command failed: {cmd}")
    
    return result