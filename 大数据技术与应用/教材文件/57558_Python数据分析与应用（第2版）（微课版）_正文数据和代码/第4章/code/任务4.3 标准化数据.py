# 代码 4-21
import pandas as pd
pay = pd.read_csv('../data/user_pay_info.csv', index_col=0)
# 自定义离差标准化函数
def min_max_scale(data):
    data = (data - data.min()) / (data.max() - data.min())
    return data
# 对用户每月支出信息表的每月支出数据做离差标准化
pay_min_max = min_max_scale(pay['每月支出'])
print('离差标准化之前每月支出数据为：\n', pay['每月支出'].head())
print('离差标准化之后每月支出数据为\n', pay_min_max.head())



# 代码 4-22
# 自定义标准差标准化函数
def standard_scaler(data):
    data = (data - data.mean()) / data.std()
    return data
# 对用户每月支出信息表的每月支出数据做标准差标准化
pay_standard = standard_scaler(pay['每月支出'])
print('标准差标准化之前每月支出数据为：\n', pay['每月支出'].head())
print('标准差标准化之后每月支出数据为：\n', pay_standard.head())



# 代码 4-23
# 自定义小数定标标准化函数
import numpy as np
def decimal_scaler(data):
    data = data / 10 ** np.ceil(np.log10(data.abs().max()))
    return data
# 对用户每月支出信息表的每月支出数据做小数定标标准化
pay_decimal = decimal_scaler(pay['每月支出'])
print('小数定标标准化之前的每月支出数据：\n', pay['每月支出'].head())
print('小数定标标准化之后的每月支出数据：\n', pay_decimal.head())

