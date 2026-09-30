"""
tree_node.py

定义系统发育树中的节点结构。
一个节点可能是：
1. 叶节点（有 name）
2. 内部节点（没有 name，但有 children）
"""

class TreeNode:

    def __init__(self, name=None):
        # 节点名称（叶节点才有）
        self.name = name

        # 子节点列表
        self.children = []

    def is_leaf(self):
        """判断是否为叶节点"""
        return len(self.children) == 0

    def add_child(self, node):
        """添加子节点"""
        self.children.append(node)

    def get_all_leaves(self):
        """
        获取该节点子树下所有叶节点名称
        """
        if self.is_leaf():
            return {self.name}

        leaves = set()

        for child in self.children:
            leaves.update(child.get_all_leaves())

        return leaves