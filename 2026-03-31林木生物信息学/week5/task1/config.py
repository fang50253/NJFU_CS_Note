"""
config.py

项目参数配置

所有参数都有默认值，可通过命令行参数覆盖。
同时提供 build_args() 函数用于构建 argparse 解析器。
"""

import argparse
import sys


# ========== 默认值（单点维护） ==========

# 默认输入路径（文件或目录）
DEFAULT_TREE_SOURCE = "trees"

# 默认目标样本集合
DEFAULT_TARGET_GROUP = {
    "A1", "A2", "A3", "A4", "A5",
    "A6", "A7", "A8", "A9", "A10"
}

# 默认宽松判定允许缺失数
DEFAULT_TOLERANCE_K = 2

# 默认输出目录
DEFAULT_OUTPUT_DIR = "output"


# ========== 命令行参数构建 ==========

def build_arg_parser():
    """
    构建命令行参数解析器。
    
    支持:
    - --tree / -t : 输入文件或目录路径
    - --target / -g : 目标样本列表（空格分隔）
    - --k / -k : 宽松判定允许缺失数
    - --output / -o : 输出目录
    """
    parser = argparse.ArgumentParser(
        description="系统发育树单系群自动判定程序",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  # 使用默认配置（从 trees/ 目录读取）
  python main.py
              
  # 指定目录
  python main.py --tree my_trees/
              
  # 指定单文件（多棵树以分号分隔）
  python main.py --tree all_trees.nwk
              
  # 指定目标样本和宽松度
  python main.py --target A1 A2 A3 A4 A5 --k 1
              
  # 指定所有参数
  python main.py --tree trees.nwk --target A1 A2 A3 A4 A5 A6 A7 A8 A9 A10 --k 2 --output results/
        """
    )
    
    parser.add_argument(
        '--tree', '-t',
        type=str,
        default=DEFAULT_TREE_SOURCE,
        help=f'输入路径：树文件或树目录（默认: {DEFAULT_TREE_SOURCE}）'
    )
    
    parser.add_argument(
        '--target', '-g',
        type=str,
        nargs='+',
        default=sorted(DEFAULT_TARGET_GROUP),
        help=f'目标样本列表，空格分隔（默认: {" ".join(sorted(DEFAULT_TARGET_GROUP))}）'
    )
    
    parser.add_argument(
        '--k', '-k',
        type=int,
        default=DEFAULT_TOLERANCE_K,
        help=f'宽松判定允许缺失的样本数（默认: {DEFAULT_TOLERANCE_K}）'
    )
    
    parser.add_argument(
        '--output', '-o',
        type=str,
        default=DEFAULT_OUTPUT_DIR,
        help=f'输出目录（默认: {DEFAULT_OUTPUT_DIR}）'
    )
    
    return parser


def parse_args(args=None):
    """
    解析命令行参数，返回配置命名空间。
    
    Args:
        args: 命令行参数列表（默认使用 sys.argv[1:]）
        
    Returns:
        argparse.Namespace，包含 tree, target, k, output 属性
    """
    parser = build_arg_parser()
    config = parser.parse_args(args)
    
    # 将 target 列表转为 set 便于集合运算
    config.target = set(config.target)
    
    # 验证 k 值合法性
    if config.k < 0:
        parser.error(f"k 值不能为负数（收到: {config.k}）")
    
    return config