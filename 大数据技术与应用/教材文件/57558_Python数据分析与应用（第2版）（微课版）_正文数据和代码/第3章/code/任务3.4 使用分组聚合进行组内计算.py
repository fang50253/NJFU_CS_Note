# 代码3-41
import pandas as pd
musicdata = pd.read_csv('../data/musicdata.csv')

musicdataGroup = musicdata[['format', 'metric', 'value_actual']].groupby(by='format')
print('分组后的音乐行业收入信息表为:', musicdataGroup)


# 代码3-42
print('音乐行业收入信息表分组后前5组每组的均值为：\n', 
       musicdataGroup.mean(). head())

print('音乐行业收入信息表分组后前5组每组的标准差为：\n', 
       musicdataGroup.std().head())

print('音乐行业收入信息表分组后前5组每组的大小为：\n', 
       musicdataGroup.size().head())


# 代码3-43
import numpy as np
print('音乐销售价格的总和与均值为：\n',
      musicdata[['number_of_records', 'value_actual']].agg([np.sum, np.mean]))


# 代码3-44
print('音乐行业收入信息表中各类型音乐产品销售数量总和与售价的均值为：\n',
      musicdata.agg({'number_of_records': np.sum, 'value_actual': np.mean}))


# 代码3-45
print('音乐行业收入信息表中各类型音乐产品销售数量总和与售价的均值为：\n',
      musicdata.agg({'number_of_records': np.sum, 'value_actual': [np.mean, np.sum]}))



# 代码3-46
# 自定义函数求两倍的和
def DoubleSum(data):
     s = data.sum() * 2
     return s
print('音乐行业收入信息表的实际销售价格两倍总和为：\n',
      musicdata.agg({'value_actual': DoubleSum}, axis=0))


# 代码3-47
# 自定义函数求两倍的和
def DoubleSum1(data):
    s = np.sum(data) * 2
    return s
print('音乐行业收入信息表的销售数量两倍总和为：\n',
      musicdata.agg({'number_of_records': DoubleSum1}, axis=0).head())

print('音乐行业收入信息表记录售卖量与实际售价的和的两倍为：\n',
      musicdata[['number_of_records', 'value_actual']].agg(DoubleSum1))


# 代码3-48
print('音乐行业收入信息表分组后前3组每组的均值为：\n', 
      musicdataGroup.agg(np.mean).head(3))

print('音乐行业收入信息表分组后前3组每组的标准差为：\n', 
      musicdataGroup.agg(np.std).head(3))


# 代码3-49
print('音乐行业收入信息表分组前3组每种销售形式的记录数和销售价格均值为：\n',
      musicdataGroup.agg([('number_of_records', 'count'), 
                          ('value_actual', 'mean')]).head(3))


# 代码3-50
print('音乐行业收入信息表的销售数量和销售价格均值为：\n',    
      musicdata[['number_of_records', 'value_actual']].apply(np.mean))


# 代码3-51
print('音乐行业收入信息表分组后前3组每组的均值为：','\n', 
      musicdataGroup.apply(np.mean).head(3))

print('音乐行业收入信息表分组后前3组每组的标准差为：','\n', 
      musicdataGroup.apply(np.std).head(3))


# 代码3-52
print('音乐行业收入信息表销售数量和销售价格的两倍为：\n',
      musicdata[['number_of_records', 'value_actual']].transform(
            lambda x: x * 2).head(4))


# 代码3-53
print('音乐行业收入信息表分组后实现组内离差标准化后前5行为：\n', 
      musicdataGroup.transform(lambda x: (x.mean()
             - x.min()) / (x.max() - x.min())).head())

