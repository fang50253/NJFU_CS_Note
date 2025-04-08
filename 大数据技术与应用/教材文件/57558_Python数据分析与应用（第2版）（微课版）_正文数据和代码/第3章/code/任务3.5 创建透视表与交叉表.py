# 代码5-54
import pandas as pd
musicdata = pd.read_csv('../data/musicdata.csv')

musicdataPivot = pd.pivot_table(musicdata[[
      'format', 'number_of_records', 'value_actual']],
      index='format')
print('以foramt作为分组键创建的订单透视表为：\n', musicdataPivot.head())


# 代码5-55
import numpy as np
musicdataPivot1 = pd.pivot_table(musicdata[[
      'format', 'number_of_records', 'value_actual']],
      index='format', aggfunc=np.sum)
print('以format作为分组键创建的销售数量与实际销售加工总和透视表为：\n',
       musicdataPivot1.head())


# 代码3-56
musicdataPivot2 = pd.pivot_table(musicdata[[
      'format', 'metric', 
      'number_of_records', 'value_actual']],
      index=['format', 'metric'],
      aggfunc=np.sum)
print('以format和metric作为分组键创建的销售数量/与销售价格总和透视表为：\n', 
      musicdataPivot2.head())


# 代码3-57
musicdataPivot3 = pd.pivot_table(musicdata[[
      'format', 'metric', 'number_of_records', 'value_actual']],
      index='format', columns='metric', aggfunc=np.sum)
print('以format和metric作为行列分组键创建的透视表前5行4列为：\n',
      musicdataPivot3.iloc[:5, :4])


# 代码3-58
musicdataPivot4 = pd.pivot_table(musicdata[[
      'format', 'metric', 'number_of_records', 'value_actual']],
      index = 'format', values='value_actual', aggfunc=np.sum)
print('以format作为行分组键value_actual作为值创建的透视表前5行为：\n', 
      musicdataPivot4.head())


# 代码3-59
musicdataPivot5 = pd.pivot_table(musicdata[[
      'format', 'metric', 'number_of_records', 'value_actual']],
      index='format', columns='metric', aggfunc=np.sum, fill_value=0)
print('空值填0后以format和metric为行列分组键创建透视表前5行4列为：\n', 
      musicdataPivot5.iloc[:5, :4])


# 代码3-60
musicdataPivot6 = pd.pivot_table(musicdata[[
      'format', 'metric', 'number_of_records', 'value_actual']],
      index='format', columns='metric', aggfunc=np.sum,
      fill_value=0, margins=True)
print('添加margins后以format和metric为分组键的透视表前5行后4列为：\n',
      musicdataPivot6.iloc[:5, -4:])
 

# 代码3-61
musicdataCross = pd.crosstab(index=musicdata['format'],
      columns=musicdata['metric'],
      values=musicdata['value_actual'], aggfunc = np.sum)
print('以format和metric为分组键value_actual为值的透视表前5行4列为：\n', 
      musicdataCross.iloc[:5, :4])



