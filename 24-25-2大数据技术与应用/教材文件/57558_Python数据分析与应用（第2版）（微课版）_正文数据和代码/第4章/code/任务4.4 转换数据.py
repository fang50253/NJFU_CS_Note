# 代码 4-24
import pandas as pd
all_info = pd.read_csv('../data/user_all_info.csv')
live_type = all_info.loc[0: 5, '居住类型']   #抽取部分数据做演示
print('哑变量处理前的数据为：\n', live_type)
print('哑变量处理后的数据为：\n', pd.get_dummies(live_type))



# 代码 4-25
age_cut = pd.cut(all_info['年龄'], 5)
print('离散化后5条记录年龄分布为：\n', age_cut.value_counts())



# 代码 4-26
import numpy as np
# 自定义等频法离散化函数
def same_rate_cut(data, k):
    w = data.quantile(np.arange(0, 1 + 1.0 / k, 1.0 / k))
    data = pd.cut(data, w)
    return data
# 对用户年龄进行等频法离散化
age_same_rate = same_rate_cut(all_info['年龄'], 5).value_counts()   
print('用户年龄数据等频法离散化后分布状况为：', '\n', age_same_rate)



# 代码 4-27
# 自定义数据K-Means聚类离散化函数
def kmean_cut(data, k):
    from sklearn.cluster import KMeans  # 引入K-Means
    # 建立模型
    kmodel = KMeans(n_clusters=k)
    kmodel.fit(data.values.reshape((len(data), 1)))  # 训练模型
    # 输出聚类中心并排序
    c = pd.DataFrame(kmodel.cluster_centers_).sort_values(0)   
    w = c.rolling(2).mean().iloc[1:]  # 相邻两项求中点，作为边界点
    w = [0] + list(w[0]) + [data.max()]  # 把首末边界点加上
    data = pd.cut(data, w)
    return data
# 用户年龄等频法离散化
all_info['年龄'].dropna(inplace=True)
age_kmeans = kmean_cut(all_info['年龄'], 5).value_counts()   
print('用户年龄聚类离散化后各个类别数目分布状况为：', '\n', age_kmeans)