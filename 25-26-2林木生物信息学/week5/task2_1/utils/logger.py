"""
日志模块
用于记录pipeline运行信息
"""

import logging
import os
from config import LOG_DIR

os.makedirs(LOG_DIR, exist_ok=True)

log_file = os.path.join(LOG_DIR, "pipeline.log")

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    handlers=[
        logging.FileHandler(log_file),
        logging.StreamHandler()
    ]
)

logger = logging.getLogger()