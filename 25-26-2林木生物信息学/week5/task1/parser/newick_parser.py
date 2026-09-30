"""
newick_parser.py

用于解析 Newick 格式的树
例如：
((A1,A2),(B1,B2),C);

支持：
- 分支长度（自动忽略，如 A1:0.02 → A1）
- NHX 注释（自动忽略，如 A1[&label=value] → A1）
- 引号包裹的名称（如 'A 1'）
"""

import re
from tree.tree_node import TreeNode


def _clean_name(token):
    """
    清理节点名称，去除分支长度和注释。
    
    处理规则：
    1. 去除首尾空白
    2. 去除 : 之后的分支长度（如 A1:0.02 → A1）
    3. 去除 [...] 中的注释（如 A1[&label=val] → A1）
    4. 去除引号（如 'A 1' → A 1）
    
    Args:
        token: 原始 token 字符串
        
    Returns:
        清理后的节点名称
    """
    name = token.strip()
    if not name:
        return name
    
    # 去除单引号或双引号包装
    if (name.startswith("'") and name.endswith("'")) or \
       (name.startswith('"') and name.endswith('"')):
        name = name[1:-1]
    
    # 去除分支长度 :number 或 :number.number
    # 只去除紧随数字的分支长度，保留名称中可能合法的冒号
    name = re.sub(r':[+-]?(\d+(\.\d*)?|\.\d+)([eE][+-]?\d+)?', '', name)
    
    # 去除 NHX 注释 [...]（在分支长度之后）
    name = re.sub(r'\[.*?\]', '', name)
    
    return name.strip()


def parse_newick(newick_str):
    """
    将 Newick 字符串解析为 TreeNode 树结构。
    
    使用基于栈的迭代算法，单遍扫描，时间复杂度 O(n)。
    忽略分支长度和注释，只关注拓扑结构。
    
    Args:
        newick_str: Newick 格式的树字符串
        
    Returns:
        树的根节点 (TreeNode)
    """
    stack = []
    current_node = TreeNode()

    token = ""

    for ch in newick_str:

        if ch == "(":
            # 进入新层级 → 创建子节点 → 入栈保存当前节点
            new_node = TreeNode()
            current_node.add_child(new_node)
            stack.append(current_node)
            current_node = new_node

        elif ch == ",":
            # 兄弟分隔符 → 处理左侧累积的 token
            name = _clean_name(token)
            if name:
                leaf = TreeNode(name)
                current_node.add_child(leaf)
            token = ""

        elif ch == ")":
            # 退出层级 → 处理 token → 出栈回退到父节点
            name = _clean_name(token)
            if name:
                leaf = TreeNode(name)
                current_node.add_child(leaf)
            token = ""

            current_node = stack.pop()

        elif ch == ";":
            # Newick 结束标记，忽略
            continue

        else:
            # 累积名称字符
            token += ch

    # 根节点在初始空 TreeNode 的第一个子节点
    return current_node.children[0]