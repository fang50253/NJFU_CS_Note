from mlxtend.frequent_patterns import apriori, association_rules
from mlxtend.preprocessing import TransactionEncoder
import pandas as pd

# 扩展的购买记录数据
data = [
    ['面包', '牛奶', '啤酒', '尿布'],
    ['面包', '牛奶', '啤酒'],
    ['啤酒', '尿布'],
    ['面包', '牛奶', '花生'],
    ['牛奶', '尿布', '啤酒', '可乐'],
    ['面包', '牛奶', '尿布', '鸡蛋'],
    ['啤酒', '尿布', '薯片'],
    ['面包', '花生酱', '果酱'],
    ['牛奶', '面包', '麦片'],
    ['啤酒', '薯片', '坚果'],
    ['尿布', '婴儿湿巾', '婴儿奶粉'],
    ['面包', '牛奶', '鸡蛋', '黄油'],
    ['啤酒', '花生', '薯片'],
    ['牛奶', '麦片', '香蕉'],
    ['面包', '奶酪', '火腿']
]

# 创建TransactionEncoder实例
te = TransactionEncoder()
te_ary = te.fit(data).transform(data)
df = pd.DataFrame(te_ary, columns=te.columns_)

# 使用apriori函数找到频繁项集
frequent_itemsets = apriori(df, min_support=0.3, use_colnames=True)

# 生成关联规则
rules = association_rules(frequent_itemsets, metric="confidence", min_threshold=0.6)

# 显示关联规则
print(rules[['antecedents', 'consequents', 'support', 'confidence', 'lift']])