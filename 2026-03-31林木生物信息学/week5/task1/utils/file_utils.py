"""
file_utils.py

读取目录中的所有 nwk 文件
"""

import os


def load_tree_files(directory):

    files = []

    for f in sorted(os.listdir(directory)):

        if f.endswith(".nwk"):
            files.append(os.path.join(directory, f))

    return files


def read_file(path):

    with open(path) as f:
        return f.read().strip()