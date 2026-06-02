"""
monophyly_checker.py

负责判断目标样本是否构成单系群
"""

def find_all_nodes(root):
    """
    获取树中所有节点
    """
    nodes = []

    def dfs(node):
        nodes.append(node)

        for child in node.children:
            dfs(child)

    dfs(root)

    return nodes


def check_strict_monophyly(root, target_set):
    """
    严格单系群判定
    条件：
    存在某节点，其所有叶节点 == target_set
    """

    nodes = find_all_nodes(root)

    for node in nodes:

        leaves = node.get_all_leaves()

        if leaves == target_set:
            return True, "存在一个节点，其叶节点集合与目标集合完全一致"

    return False, "不存在叶节点集合与目标集合完全一致的内部节点"


def check_tolerant_monophyly(root, target_set, tolerance_k):
    """
    宽松判定

    条件：
    1. 节点下不能出现非目标样本
    2. 允许缺失 <= k
    """

    nodes = find_all_nodes(root)

    for node in nodes:

        leaves = node.get_all_leaves()

        # 不允许混入非目标样本
        if not leaves.issubset(target_set):
            continue

        missing = target_set - leaves

        if len(missing) <= tolerance_k:
            return True, missing

    # 注意这里！！！
    return False, set()