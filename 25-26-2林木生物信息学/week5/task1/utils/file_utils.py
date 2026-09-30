"""
file_utils.py

树文件加载工具，支持两种输入模式：
1. 目录模式：读取目录中所有 .nwk 文件（每个文件一棵树）
2. 单文件模式：读取一个包含多棵树的文本文件（用 ; 分隔）

返回格式：[(tree_name, newick_string), ...]
"""

import os


def read_file(path):
    """
    读取文件内容。
    
    Args:
        path: 文件路径
        
    Returns:
        文件内容字符串（去除首尾空白）
    """
    with open(path, encoding='utf-8') as f:
        return f.read().strip()


def load_trees_from_file(filepath):
    """
    从单个文件中读取多棵以 ; 分隔的 Newick 树。
    
    支持两种分隔方式：
    - 整个文件内容以 ; 为单位拆分（忽略空字符串）
    - 每行一棵树（以换行分隔）
    
    Args:
        filepath: 树文件路径
        
    Returns:
        [(tree_name, newick_string), ...]
    """
    content = read_file(filepath)
    if not content:
        return []
    
    # 去除空白字符，统一处理
    content = content.strip()
    
    # 方式1：按分号拆分（每棵树以 ; 结束）
    # 先尝试按 ; 拆分
    parts = [p.strip() for p in content.split(';') if p.strip()]
    
    if len(parts) > 1:
        # 确实包含多棵树（;拆分出多个非空段）
        trees = []
        for i, part in enumerate(parts, 1):
            # 补回分号确保 Newick 语法正确
            newick = part.strip() + ';'
            basename = os.path.splitext(os.path.basename(filepath))[0]
            trees.append((f"{basename}_{i:03d}", newick))
        return trees
    
    # 方式2：可能是单棵树（整个文件是一棵树）
    # 如果内容没有分号结尾，补一个
    newick = content if content.endswith(';') else content + ';'
    basename = os.path.splitext(os.path.basename(filepath))[0]
    return [(basename, newick)]


def load_trees_from_directory(directory):
    """
    从目录中读取所有 .nwk 文件（每个文件一棵树）。
    
    Args:
        directory: 目录路径
        
    Returns:
        [(tree_name, newick_string), ...]
    """
    trees = []
    for f in sorted(os.listdir(directory)):
        if f.endswith(".nwk"):
            path = os.path.join(directory, f)
            newick = read_file(path)
            if newick:
                trees.append((f, newick))
    return trees


def load_trees(source):
    """
    统一入口：自动识别 source 是文件还是目录，并加载其中的树。
    
    Args:
        source: 文件路径或目录路径
        
    Returns:
        [(tree_name, newick_string), ...]
    """
    if not os.path.exists(source):
        raise FileNotFoundError(f"路径不存在: {source}")
    
    if os.path.isdir(source):
        return load_trees_from_directory(source)
    elif os.path.isfile(source):
        return load_trees_from_file(source)
    else:
        raise ValueError(f"不支持的路径类型: {source}")