import numpy as np
import pandas as pd
from sklearn.svm import SVR
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler 
from sklearn.metrics import mean_squared_error, r2_score







# 实训1:
# 读取英雄联盟游戏数据集
data=pd.read_csv("./lol.csv",encoding='gbk')
ori_data=data.copy()
print(data.head())
print(data)

# 检测并处理重复数据
data.drop_duplicates(inplace=True)
data.reset_index(drop=True, inplace=True)
print(f"删除了 {len(ori_data) - len(data)} 行重复数据")

# 删除蓝方击杀大龙数和红方击杀大龙数特征
data.drop(['蓝方击杀大龙数', '红方击杀大龙数'], axis=1, inplace=True)

# 删除双方击杀小龙数为4的行数据
data.drop(data[(data['蓝方击杀小龙数'] == 4) & (data['红方击杀小龙数'] == 4)].index, inplace=True)

# 删除红方击杀野怪数小于20的行数据
data.drop(data[data['红方击杀野怪数'] < 20].index, inplace=True)

# 对全部数据进行重新索引
data.reset_index(drop=True, inplace=True)

print(f"数据集大小: {data.shape}")
print(data)




# 实训2:
# 构建经济差、等级差、击杀小兵数量差、击杀野怪数量差、击杀英雄数量差、击杀小龙数量差、推塔数量差共7个新特征
data['经济差']=data['蓝方经济']-data['红方经济']
data['等级差']=data['蓝方平均等级']-data['红方平均等级']
data['击杀小兵数量差']=data['蓝方击杀小兵数']-data['红方击杀小兵数']
data['击杀野怪数量差']=data['蓝方击杀野怪数']-data['红方击杀野怪数']
data['击杀英雄数量差']=data['蓝方击杀英雄数']-data['红方击杀英雄数']
data['击杀小龙数量差']=data['蓝方击杀小龙数']-data['红方击杀小龙数']
data['推塔数量差']=data['蓝方被推塔数']-data['红方被推塔数']

# 正常对局中，当双方经济差在2000以内时，难以预测游戏最终胜负情况，需丢弃经济差在2000以内的数据
data.drop(data[(data['经济差'] < 2000) & (data['经济差'] > -2000)].index, inplace=True)

# 对全部数据进行重新索引
data.reset_index(drop=True, inplace=True)
print(f"数据集大小: {data.shape}")
print(data)





# 实训3:
# 拆分输入特征与标签
data_x=data.drop(['蓝方获胜情况'], axis=1)
data_y=data['蓝方获胜情况']

# 划分训练集和测试集
data_x_train=data_x[:int(len(data_x)*0.8)]
data_x_test=data_x[int(len(data_x)*0.8):]
data_y_train=data_y[:int(len(data_y)*0.8)]
data_y_test=data_y[int(len(data_y)*0.8):]

# 对训练集和验证集分别进行标准差标准化
data_x_train=(data_x_train-data_x_train.mean())/data_x_train.std()
data_x_test=(data_x_test-data_x_train.mean())/data_x_train.std()

# 构建SVR模型，并进行模型的训练和预测
data_x_train=data_x_train.values
data_x_test=data_x_test.values
svr=SVR(kernel='linear',C=1.0,epsilon=0.33)
svr.fit(data_x_train,data_y_train)
data_y_predict=svr.predict(data_x_test)

# 输出回归模型评价指标，查看模型效果
print("均方误差:", mean_squared_error(data_y_test, data_y_predict))
print("R2分数:", r2_score(data_y_test, data_y_predict))
print("SVR模型训练完成，预测结果如下：")
print(data_y_predict)