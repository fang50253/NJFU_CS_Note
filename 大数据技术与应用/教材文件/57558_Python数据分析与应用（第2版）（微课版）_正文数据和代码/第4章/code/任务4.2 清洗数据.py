# 代码 4-7
import pandas as pd
download = pd.read_csv('../data/user_download.csv', 
                       index_col=0, encoding='gbk')
# 方法一
# 定义去重函数
def del_rep(list1):
    list2 = []
    for i in list1:
        if i not in list2:
            list2.append(i)
    return list2 
# 去重
# 将下载意愿从数据框中提取出来
download = list(download['是否愿意下载'])  
print('去重前下载意愿选项总数为：', len(download)) 
download_rep = del_rep(download)  # 使用自定义的去重函数去重
print('方法一去重后下载意愿选项总数为：', len(download_rep))
print('用户选项为：', download_rep)



# 代码 4-8
# 方法二
print('去重前下载意愿选项总数为：', len(download)) 
download_set = set(download)  # 利用set的特性去重
print('方法二去重后下载意愿选项总数为：', len(download_set))
print('用户选项为：', download_set)



# 代码 4-9
# 对下载意愿去重
download = pd.read_csv('../data/user_download.csv', 
                       encoding='gbk')
download_select = download['是否愿意下载'].drop_duplicates() 
print('drop_duplicates方法去重之后下载意愿选项总数为：', 
      len(download_select))



# 代码 4-10
all_info = pd.read_csv('../data/user_all_info.csv')
print('去重之前用户的形状为：', all_info.shape)
shape_det = all_info.drop_duplicates(subset = ['用户编号', 
                                               '编号']).shape
print('依照用户编号，编号去重之后用户总信息表大小为:', shape_det)



# 代码 4-11
# 求取年龄和每月支出的相似度
corr_det = all_info[['年龄', '每月支出']].corr(method='kendall')
print('年龄和每月支出的相似度矩阵为：\n', corr_det)



# 代码 4-12
corr_det1 = all_info[['居住类型', '年龄', '每月支出'
                      ]].corr(method='pearson')
print('居住类型、年龄和每月支出的pearson法相似度矩阵为：\n', corr_det1)



# 代码 4-13
# 定义求取特征是否完全相同的矩阵的函数
def feature_equals(df):
    df_equals = pd.DataFrame([])
    for i in df.columns:
        for j in df.columns:
            df_equals.loc[i, j] = df.loc[:, i].equals(df.loc[:, j])
    return df_equals
# 应用上述函数
app_desire = feature_equals(all_info)
print('app_desire的特征相等矩阵的前7行7列为：\n', 
      app_desire.iloc[:7, :7])



# 代码 4-14
# 遍历所有数据
len_feature = app_desire.shape[0]
dup_col = []
for m in range(len_feature):
    for n in range(m + 1, len_feature):
        if app_desire.iloc[m, n] & (app_desire.columns[n] 
                                    not in dup_col):
            dup_col.append(app_desire.columns[n])
#进行去重操作
print('需要删除的行为：', dup_col)
all_info.drop(dup_col, axis=1, inplace=True)
print('删除多余行后all_info的特征数目为：', all_info.shape[1])



# 代码 4-15
print('all_info每个特征缺失的数目为：\n', all_info.isnull().sum())
print('all_info每个特征非缺失的数目为：\n', all_info.notnull().sum())



# 代码 4-16
print('去除缺失的行前all_info的形状为：', all_info.shape)
all_info1 = all_info.dropna(axis=0, how='any')
print('去除缺失的行后all_info的形状为：', all_info1.shape)
all_info1.to_csv('../tmp/all_info_notnull.csv', index=False)



# 代码 4-17
# 求每月支出平均值
mean_num = all_info['每月支出'].mean()
# 缺失值替换为均值
all_info['每月支出'] = all_info['每月支出'].fillna(mean_num)
print('每月支出特征缺失的数目为：\n', 
      all_info['每月支出'].isnull().sum())



# 代码 4-18
# 线性插值
import numpy as np
from scipy.interpolate import interp1d
# 创建自变量x
x = np.array([1, 2, 3, 4, 5, 8, 9, 10])  
# 创建因变量y1
y1 = np.array([2, 8, 18, 32, 50, 128, 162, 200])  
# 创建因变量y2
y2 = np.array([3, 5, 7, 9, 11, 17, 19, 21])  
# 线性插值拟合x、y1
linear_ins_value1 = interp1d(x, y1, kind='linear')  
# 线性插值拟合x、y2
linear_ins_value2 = interp1d(x, y2, kind='linear')  
print('当x为6、7时，使用线性插值y1为：', linear_ins_value1([6, 7]))
print('当x为6、7时，使用线性插值y2为：', linear_ins_value2([6, 7]))

# 拉格朗日插值
from scipy.interpolate import lagrange
large_ins_value1 = lagrange(x, y1)  # 拉格朗日插值拟合x、y1
large_ins_value2 = lagrange(x, y2)  # 拉格朗日插值拟合x、y2
print('当x为6,7时，使用拉格朗日插值y1为：', large_ins_value1([6, 7]))
print('当x为6,7时，使用拉格朗日插值y2为：', large_ins_value2([6, 7]))

# 样条插值
# 样条插值拟合x、y1
y1_new = np.linspace(x.min(), x.max(), 10)
f = interp1d(x, y1, kind='cubic')  # 编辑插值函数格式
spline_ins_value1 = f(y1_new) # 通过相应的插值函数求得新的函数点
# 样条插值拟合x、y2
y2_new = np.linspace(x.min(), x.max(), 10)
f = interp1d(x, y2, kind='cubic')  # 编辑插值函数格式
spline_ins_value2 = f(y2_new) # 通过相应的插值函数求得新的函数点
print('使用样条插值y1为：', spline_ins_value1)
print('使用样条插值y2为：', spline_ins_value2)



# 代码 4-19
all_info = pd.read_csv('../tmp/all_info_notnull.csv')
# 定义3σ原则来识别异常值函数
def out_range(ser1):
    bool_ind = (ser1.mean() - 3 * ser1.std() > ser1) | \
    (ser1.mean() + 3 * ser1.var() < ser1)
    index = np.arange(ser1.shape[0])[bool_ind]
    outrange = ser1.iloc[index]
    return outrange
outlier = out_range(all_info['年龄'])
print('使用3σ原则判定异常值个数为:', outlier.shape[0])
print('异常值的最大值为：', outlier.max())
print('异常值的最小值为：', outlier.min())



# 代码 4-20
import matplotlib.pyplot as plt
plt.figure(figsize=(10, 8), dpi=1080) 
p = plt.boxplot(list(all_info['年龄'].values))  # 画出箱线图
outlier1 = p['fliers'][0].get_ydata()  # fliers为异常值的标签
plt.savefig('../tmp/用户年龄异常数据识别.jpg')
plt.show()
print('年龄数据异常值个数为：', len(outlier1))
print('年龄数据异常值的最大值为：', max(outlier1))
print('年龄数据异常值的最小值为：', min(outlier1))

