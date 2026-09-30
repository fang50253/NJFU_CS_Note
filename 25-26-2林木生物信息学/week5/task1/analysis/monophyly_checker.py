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


def find_mrca(root, target_set):
    """
    找到包含全部目标样本的"最小包含节点"(MRCA, Most Recent Common Ancestor)。
    即：该节点的叶节点集合包含全部目标样本，但其任意子节点都不包含全部目标样本。
    返回 (mrca_node, mrca_leaves)，若不存在这样的节点则返回 (None, None)。
    """
    nodes = find_all_nodes(root)
    for node in nodes:
        leaves = node.get_all_leaves()
        if not target_set.issubset(leaves):
            continue
        # 检查是否有子节点也能包含全部目标样本
        child_also_contains = False
        for child in node.children:
            if target_set.issubset(child.get_all_leaves()):
                child_also_contains = True
                break
        if not child_also_contains:
            return node, leaves
    return None, None


def check_strict_monophyly(root, target_set, tolerance_k=2):
    """
    严格单系群判定
    条件：存在某节点，其所有叶节点 == target_set

    失败时区分三种原因：
    1）不存在叶节点集合与目标集合完全一致的内部节点：存在纯净分支但缺失部分目标样本
    2）混入非目标样本：所有目标样本能被同一节点包含，但混入了非目标样本
    3）目标样本被分散：目标样本分布过于分散，无单一节点能包含全部
    
    (三种原因对应项目说明中的示例输出)
    
    Args:
        root: 树根节点
        target_set: 目标样本集合
        tolerance_k: 用于失败原因分析的宽松阈值（默认2），
                     仅当纯净分支包含至少 len(target_set)-tolerance_k 个样本时，
                     才将失败原因归为"目标样本缺失"而非"分散"
    """

    nodes = find_all_nodes(root)

    # 第一步：检查是否存在完美匹配
    for node in nodes:
        leaves = node.get_all_leaves()
        if leaves == target_set:
            return True, "存在一个节点，其叶节点集合与目标集合完全一致"

    # 第二步：寻找最大的纯净（只含目标样本）节点
    # 如果存在一个几乎完整的纯净分支但缺失了少量目标样本 → "目标样本缺失"
    MIN_PURE_FOR_MISSING = len(target_set) - tolerance_k
    best_pure_count = 0
    best_pure_missing = None
    for node in nodes:
        leaves = node.get_all_leaves()
        if leaves.issubset(target_set) and len(leaves) > best_pure_count:
            best_pure_count = len(leaves)
            best_pure_missing = target_set - leaves

    if best_pure_count >= MIN_PURE_FOR_MISSING and best_pure_missing:
        return False, (
            f"不存在叶节点集合与目标集合完全一致的内部节点"
            f"（目标样本缺失: {sorted(best_pure_missing)}，"
            f"最接近的纯净分支包含{best_pure_count}个目标样本）"
        )

    # 第三步：检查MRCA（最小包含节点）是否有非目标样本混入
    mrca, mrca_leaves = find_mrca(root, target_set)
    if mrca is not None:
        extra = mrca_leaves - target_set
        if extra:
            return False, f"包含全部目标样本的节点中混入了非目标样本: {sorted(extra)}"

    # 第四步：目标样本被分散
    return False, "目标样本被分散在多个分支中，不存在能包含全部目标样本的单一内部节点"


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