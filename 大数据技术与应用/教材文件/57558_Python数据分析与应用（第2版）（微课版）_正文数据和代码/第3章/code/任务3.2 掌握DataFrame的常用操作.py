# 代码3-9
from sqlalchemy import create_engine
import pandas as pd
# 创建数据库连接
engine = create_engine('mysql+pymysql://root:1234@127.0.0.1:3306/testdb?charset=utf8') 
musicdata = pd.read_sql_table('musicdata', con=engine)
print('音乐行业收入信息表的索引为：', musicdata.index)

print('音乐行业收入信息表的所有值为：\n', musicdata.values)

print('音乐行业收入信息表的列名为：\n', musicdata.columns)

print('音乐行业收入信息表的数据类型为：\n', musicdata.dtypes)



# 代码3-10
# 查看DataFrame的元素个数、维度数、形状
print('音乐行业收入信息表的元素个数为：', musicdata.size) 
print('音乐行业收入信息表的维度数为：', musicdata.ndim)
print('音乐行业收入信息表的形状为：', musicdata.shape)


# 代码3-11
print('音乐行业收入信息表转置前形状为：', musicdata.shape)
print('音乐行业收入信息表转置后形状为：', musicdata.T.shape)


# 代码3-12
# 使用字典访问的方式取出musicdata中的某一列
format = musicdata['format']
print('音乐行业收入信息表中的format的形状为：', format.shape)


# 代码3-13
# 使用访问属性的方式取出musicdata中的number_of_records
number_of_records = musicdata.number_of_records
print('音乐行业收入信息表中的number_of_records的形状为:', number_of_records.shape)


# 代码3-14
metric5 = musicdata['metric'][:5]
print('音乐行业收入信息表中的metric前5个元素为：\n', metric5)


# 代码3-15
format_metric = musicdata[['format', 'metric']][:5]
print('音乐行业收入信息表中的format和metric前5个元素为：\n', format_metric)


# 代码3-16
musicdata5 = musicdata[:][1:6]
print('音乐行业收入信息表的1～6行元素为：\n', musicdata5)


# 代码3-17
print('音乐行业收入信息表中前5行数据为:\n', musicdata.head())

print('音乐行业收入信息表中后5行元素为：\n', musicdata.tail())


# 代码3-18
format1 = musicdata.loc[:, 'format']
print('使用loc()方法提取format列的size为：', format1.size)

format2 = musicdata.iloc[:, 3]
print('使用iloc()方法提取第3列的size为：', format2.size)


# 代码3-19
format_metric1 = musicdata.loc[:, ['format', 'metric']]
print('使用loc()方法提取format和metric列的size为：', format_metric1.size)    

format_metric2 = musicdata.iloc[:, [1, 3]]
print('使用iloc()方法提取第1和第3列的size为：', format_metric2.size)


# 代码3-20
print('列名为format和metric的行名为3的数据为：\n',
      musicdata.loc[3, ['format', 'metric']])

print('列名为format和metric行名为2,3,4,5,6的数据为：\n',
      musicdata.loc[2: 6, ['format', 'metric']])

print('列位置为1和3，行位置为3的数据为：\n', musicdata.iloc[3, [1, 3]])

print('列位置为1和3，行位置为2,3,4,5,6的数据为：\n',
      musicdata.iloc[2: 7, [1, 3]])


# 代码3-21
# 传入表达式
print('musicdata中metric为“Units”的format为：\n',
       musicdata.loc[musicdata['metric'] == 'Units', ['format', 'metric']])

print('musicdata中metric为“Units”的第1、4列数据为：\n',
     musicdata.iloc[musicdata['metric'] == 'Units', [1, 4]])


# 代码3-22
print('musicdata中metric为“Units”的第1、4列数据为：\n',
      musicdata.iloc[(musicdata['metric'] == 'Units').values, [1, 4]])


# 代码3-23
# 将format值为CD的变换为数值1
print('更改前musicdata中format为CD的数据为：\n',
      musicdata.loc[musicdata['format'] == 'CD', 'format'])
musicdata.loc[musicdata['format'] == 'CD', 'format']=1
print('更改后musicdata中format为1的数据为：\n',
     musicdata.loc[musicdata['format'] == 1, 'format'])


# 代码3-24
# 转换为时间序列数据
dates = pd.to_datetime(musicdata['date'])
# 建立月份列
musicdata['month'] = dates.map(lambda x: x.month)
# 查看前5行
print('musicdata新增列month的前5行为：\n', musicdata['month'].head())


# 代码3-25
musicdata['day'] = 15
print('musicdata新增列day的前5行为：\n', musicdata['day'].head())


# 代码3-26
print('删除day前musicdata的列索引为：\n', musicdata.columns)
musicdata.drop(labels='day', axis=1, inplace=True)
print('删除day后musicdata的列索引为：\n', musicdata.columns)


# 代码3-27
print('删除1～3行前musicdata的长度为：', len(musicdata))
musicdata.drop(labels=range(1, 4), axis=0, inplace=True)
print('删除1～3行后musicdata的长度为：', len(musicdata))


# 代码3-28
import numpy as np
print('音乐行业收入信息表中number_of_records的平均值为：', 
      np.mean(musicdata['number_of_records']))

# 代码3-29
print('音乐行业收入信息表中number_of_records的平均值为：', 
      musicdata['number_of_records'].mean())


# 代码3-30
print('音乐行业收入信息表value_actual的描述性统计为：\n',
     musicdata['value_actual'].describe())


# 代码3-31
print('音乐行业收入信息 表format频数统计前6行结果为：\n',
     musicdata['format'].value_counts()[:6])


# 代码3-32
musicdata['metric'] = musicdata['metric'].astype('category')
print('音乐行业收入信息表metric列转变数据类型后为：',
   musicdata['metric'].dtypes)  


# 代码3-33
print('音乐行业收入信息表metric的描述统计结果为：\n',
    musicdata['metric'].describe())






