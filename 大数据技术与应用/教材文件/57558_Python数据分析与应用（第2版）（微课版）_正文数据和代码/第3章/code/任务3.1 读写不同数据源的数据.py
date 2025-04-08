# 代码3-1
import pandas as pd
# 使用read_table函数读取音乐行业收入信息表
musicdata = pd.read_table('../data/musicdata.csv', sep=',', encoding='gbk')
print('使用read_table函数读取音乐行业收入信息表的长度为：', len(musicdata))

# 使用read_csv函数读取音乐行业收入信息表
musicdata1 = pd.read_csv('../data/musicdata.csv', encoding='gbk')
print('使用read_csv函数读取音乐行业收入信息表的长度为：', len(musicdata1))


# 代码3-2
# 使用read_table函数读取音乐行业收入表，sep=';'
musicdata2 = pd.read_table('../data/musicdata.csv', sep = ';', encoding='gbk')
print('当分隔符为;时，音乐行业收入信息表为：\n', musicdata2)

# 使用read_csv函数读取音乐行业收入信息表，header=None
musicdata3 = pd.read_csv('../data/musicdata.csv', sep=',', header=None, encoding='gbk')
print('当header为None时，音乐行业收入数据信息表为：\n', musicdata3)

# 使用UTF-16编码读取音乐行业收入信息表
musicdata4 = pd.read_csv('../data/musicdata.csv', sep=',', encoding='utf-16')
print('encoding为"utf-16"时音乐行业收入数据信息表为：\n', musicdata4)


# 代码3-3
import os
print('音乐行业收入信息表写入文本文件前目录内文件列表为：\n', os.listdir('../tmp')) 
# 将musicdata以csv格式存储
musicdata.to_csv('../tmp/musicdataInfo.csv', sep=';', index=False) 
print('音乐行业收入信息表写入文本文件后目录内文件列表为：\n', os.listdir('../tmp'))


# 代码3-4
# 读取musicdata.xlsx文件
musicdata = pd.read_excel('../data/musicdata.xlsx')
print('音乐行业收入信息表长度为：', len(musicdata))


# 代码3-5
print('音乐行业收入信息表写入Excel文件前，目录内文件列表为：\n', os.listdir('../tmp')) 
musicdata.to_excel('../tmp/musicdata.xlsx')
print('音乐行业收入信息表写入Excel文件后，目录内文件列表为：\n', os.listdir('../tmp'))


# 代码3-6
from sqlalchemy import create_engine
# 创建一个MySQL连接器，用户名为root，密码为1234
# 地址为127.0.0.1，数据库名称为testdb，编码为UTF-8
engine = create_engine('mysql+pymysql://root:1234@127.0.0.1:3306/testdb?charset=utf8')
print(engine)


# 代码3-7
# 使用read_sql_query函数查看testdb中的数据表数目
musicadatalist = pd.read_sql_query('show tables', con=engine)
print('testdb数据库数据表清单为:\n', musicadatalist)

# 使用read_sql_table函数读取音乐行业收入信息表
musicdata = pd.read_sql_table('musicdata', con=engine)
print('使用read_sql_table函数读取音乐行业收入信息表的长度为:\n', len(musicdata))

# 使用read_sql函数读取音乐行业收入信息表
musicdata = pd.read_sql('musicdata', con=engine)
print('使用read_sql函数读取音乐行业收入信息表的长度为:\n', len(musicdata))



# 代码3-8
# 使用to_sql()方法存储musicData
musicdata.to_sql('test1', con=engine, index=False, if_exists='replace')    
# 使用read_sql函数读取test表
formlist1 = pd.read_sql_query('show tables', con=engine)
print('新增一个表格后，testdb数据库数据表清单为：\n', formlist1)



