# 代码3-34
import pandas as pd
musicdata = pd.read_table('../data/musicdata.csv', sep=',', encoding='gbk') 
# 输出转换前的原始date列的类型
print('进行转换前date的类型为：', musicdata['date'].dtypes)
# 使用to_datetime函数将data列的数据类型转换成标准时间类型
musicdata['date'] = pd.to_datetime(musicdata['date'])
print('进行转换后date的类型为：', musicdata['date'].dtypes)


# 代码3-35
print('最小时间为：', pd.Timestamp.min)  # 查询计算机中最早的时间信息
print('最大时间为：', pd.Timestamp.max)  # 查询计算机中最晚的时间信息


# 代码3-36
# 将data列数据格式转换成DatetimeIndex格式
dateIndex = pd.DatetimeIndex(musicdata['date'])
print('转换为DatetimeIndex后数据的类型为：\n', type(dateIndex))

# 将data列数据格式转换成PeriodIndex格式
periodIndex = pd.PeriodIndex(musicdata['date'], freq='S')
print('转换为PeriodIndex后数据的类型为：\n', type(periodIndex))


# 代码3-37
year1 = [i.year for i in musicdata['date']]
print('date中的年份数据前5个为：', year1[:5])
month1 = [i.month for i in musicdata['date']]
print('date中的月份数据前5个为：', month1[:5])
day1 = [i.day for i in musicdata['date']]
print('date中的日期数据前5个为：', day1[:5])


# 代码3-38
# 提取DatetimeIndex中的前5个星期标号数据
print('dateIndex中的星期标号数据前5个为：\n',
       dateIndex.weekday[:5])      
# 提取PeriodIndex中的前5个星期标号数据
print('periodIndex中的星期标号数据前5个为：',
       periodIndex.weekday[:5])


# 代码3-39
# 将date数据向后平移一天
time1 = musicdata['date'] + pd.Timedelta(days=1) 
print('date加上一天前前5行数据为：\n', musicdata['date'][:5])
print('date加上一天前前5行数据为：\n', time1[:5])


# 代码3-40
# 将data数据与指定的时间数据进行相减
timeDelta = musicdata['date'] - pd.to_datetime('2020-1-1')
print('date减去2020年1月1日0点0时0分后的数据：\n', timeDelta[:5])
print('date减去time1后的数据类型为：', timeDelta.dtypes)
 



