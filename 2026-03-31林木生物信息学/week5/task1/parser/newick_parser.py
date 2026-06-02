"""
newick_parser.py

用于解析 Newick 格式的树
例如：
((A1,A2),(B1,B2),C);
"""

from tree.tree_node import TreeNode


def parse_newick(newick_str):
    """
    将 Newick 字符串解析为 TreeNode 树结构
    """

    stack = []
    current_node = TreeNode()

    token = ""

    for ch in newick_str:

        if ch == "(":
            new_node = TreeNode()
            current_node.add_child(new_node)
            stack.append(current_node)
            current_node = new_node

        elif ch == ",":
            if token.strip():
                leaf = TreeNode(token.strip())
                current_node.add_child(leaf)
                token = ""

        elif ch == ")":
            if token.strip():
                leaf = TreeNode(token.strip())
                current_node.add_child(leaf)
                token = ""

            current_node = stack.pop()

        elif ch == ";":
            continue

        else:
            token += ch

    return current_node.children[0]