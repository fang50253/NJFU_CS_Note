"""
运行shell命令
"""

import subprocess
from utils.logger import logger


def run_command(cmd):
    """
    执行shell命令
    """

    logger.info(f"Running: {cmd}")

    process = subprocess.run(
        cmd,
        shell=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    if process.returncode != 0:
        logger.error(process.stderr)
        raise RuntimeError("Command failed")

    logger.info(process.stdout)

    return process.stdout