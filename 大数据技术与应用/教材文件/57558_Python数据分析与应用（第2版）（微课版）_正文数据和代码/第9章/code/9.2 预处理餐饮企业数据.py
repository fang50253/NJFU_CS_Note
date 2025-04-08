# 代码9-1
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# 读取数据
users = pd.read_csv('../data/user_loss.csv', encoding='gbk')
info = pd.read_csv('../data/info_new.csv', encoding='utf-8')
print('客户信息表的维数：', users.shape)
print('订单详情表的维数：', info.shape)

# 将时间转为时间格式
users['CREATED'] = pd.to_datetime(users['CREATED'])
info['use_start_time'] = pd.to_datetime(info['use_start_time'])
info['lock_time'] = pd.to_datetime(info['lock_time'])

# 客户流失与年龄的关系
a = users.loc[users['TYPE'] == '已流失', ['AGE', 'TYPE']]['AGE'].value_counts().sort_index()
b = users.loc[users['TYPE'] == '非流失', ['AGE', 'TYPE']]['AGE'].value_counts().sort_index()
c = users.loc[users['TYPE'] == '准流失', ['AGE', 'TYPE']]['AGE'].value_counts().sort_index()

df = pd.DataFrame({'已流失': a.values,
                   '非流失': b.values,
                   '准流失': c.values},
                   index=range(20, 61, 1))
plt.rcParams['font.sans-serif'] = 'SimHei'  # 设置中文显示
plt.rcParams['axes.unicode_minus'] = False
plt.figure(figsize=(8, 4))
sns.lineplot(data=df)
plt.xlabel('年龄（岁）')
plt.ylabel('客户流失数量（人）')
plt.title('客户流失数量与年龄的关系')



# 代码9-2
count1 = pd.DataFrame(users[users['SEX']=='男']['TYPE'].value_counts())
count1.columns=['数量（人）']
count2 = pd.DataFrame(users[users['SEX']=='女']['TYPE'].value_counts())
count2.columns=['数量（人）']
index1 = count1.index
index2 = count2.index

fig,axes=plt.subplots(1, 2, figsize=(8, 4))
sns.barplot(x=index1, y=count1['数量（人）'], ax=axes[0])
axes[0].set_title('男性客户流失状态数量')
sns.barplot(x=index2, y=count2['数量（人）'], ax=axes[1])
axes[1].set_title('女性客户流失状态数量')



# 代码9-3
print('订单详情表重复值个数：',
     info.duplicated(subset=['name', 'use_start_time']).sum())



# 代码9-4
ind = info[info.duplicated(['dining_table_id', 'use_start_time'])].index
print('同一时间桌子被不同人使用的订单：\n',
     info[(info['dining_table_id'] == info.iloc[ind[1], :]['dining_table_id']) & 
     (info['use_start_time'] == info.iloc[ind[1], :]['use_start_time'])]
     [['info_id', 'dining_table_id','use_start_time']])

info.drop(index=ind, inplace=True)
info = info.reset_index(drop=True)
print('异常值个数：', len(ind))
print('去除异常值订单详情表维数：', info.shape)



# 代码9-5
print('客户信息表缺失值个数：', info.isnull().sum().sum())
print('订单详情表缺失值个数：', users.isnull().sum().sum())



# 代码9-6
# 获取最后一次用餐时间
for i in range(len(users)):
    info1 = info.iloc[info[info['name'] == users.iloc[i, 2]].index.tolist(), :]
    if sum(info['name'] == users.iloc[i, 2]) != 0:
        users.iloc[i, 14] = max(info1['use_start_time'])
# 获取订单状态为1的订单
info = info.loc[info['order_status'] == 1, ['emp_id', 'number_consumers', 'expenditure']]
info = info.rename(columns={'emp_id': 'USER_ID'})  # 修改列名
user = users[['USER_ID', 'LAST_VISITS', 'TYPE']]

# 合并两个表
info_user = pd.merge(user, info, left_on='USER_ID', right_on='USER_ID', how='left')
print('合并表缺失值个数：\n', info_user.isnull().sum())
info_user.dropna(inplace=True)

info_user.to_csv('../tmp/info_user.csv', index=False, encoding='utf-8')

print('处理缺失值数据维度：\n', info_user.shape)



# 代码9-7
# 构建特征
info_user = pd.read_csv('../tmp/info_user.csv', encoding='utf-8')

# 统计每个客户的用餐次数
info_user1 = info_user['USER_ID'].value_counts()
info_user1 = info_user1.reset_index()
info_user1.columns = ['USER_ID', 'frequence']  # 修改列名

# 求出每个客户的消费总金额
# 分组求和
info_user2 = info_user[['number_consumers',
                        'expenditure']].groupby(info_user['USER_ID']).sum()
info_user2 = info_user2.reset_index()
info_user2.columns = ['USER_ID', 'numbers', 'amount']
# 合并客户的用餐次数和消费总金额
data_new = pd.merge(info_user1, info_user2,
                      left_on='USER_ID', right_on='USER_ID', how='left')

# 提取数据
info_user = info_user.iloc[:, :4]
info_user = info_user.groupby(['USER_ID']).last()
info_user = info_user.reset_index()
# 合并
info_user_new = pd.merge(data_new, info_user,
                      left_on='USER_ID', right_on='USER_ID', how='left')
print(info_user_new.head())

# 求人均消费金额，并保留2为小数
info_user_new['average'] = info_user_new['amount'] / info_user_new['numbers']
info_user_new['average'] = info_user_new['average'].apply(lambda x: '%.2f' % x)

# 计算每个客户最近一次点餐的时间距离观测窗口结束的天数
# 修改时间列，改为日期
info_user_new['LAST_VISITS'] = pd.to_datetime(info_user_new['LAST_VISITS'])
datefinally = pd.to_datetime('2016-7-31')  # 观测窗口结束时间
time = datefinally - info_user_new['LAST_VISITS']
info_user_new['recently'] = time.apply(lambda x: x.days)  # 计算时间差
# 特征选取
info_user_new = info_user_new.loc[:, ['USER_ID', 'frequence',
                             'amount', 'average', 'recently', 'TYPE']]
info_user_new.to_csv('../tmp/info_user_clear.csv', index=False, encoding='gbk')
print(info_user_new.head())








