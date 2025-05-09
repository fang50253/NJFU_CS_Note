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


# ========= 1. 读取数据（保持不变） =========
data = pd.read_csv("./lol.csv", encoding="gbk")

# ========= 2. 拆分输入特征与标签 =========
data_x = data.drop(['蓝方获胜情况'], axis=1)
data_y = data['蓝方获胜情况']

# ========= 3. 划分训练集和测试集（按 8:2）=========
split_idx = int(len(data_x) * 0.8)
data_x_train, data_x_test = data_x[:split_idx], data_x[split_idx:]
data_y_train, data_y_test = data_y[:split_idx], data_y[split_idx:]

# ========= 4. 对特征进行标准差标准化（手动，与原代码一致）=========
data_x_train = (data_x_train - data_x_train.mean()) / data_x_train.std()
data_x_test  = (data_x_test  - data_x_train.mean()) / data_x_train.std()

# ========= 5. 对标签 data_y 进行 **标准化** =========
# 说明：SVR 对 y 的尺度也敏感，尤其在取值范围大或分布偏斜时。
scaler_y = StandardScaler()                                # 创建缩放器
data_y_train_scaled = scaler_y.fit_transform(
    data_y_train.values.reshape(-1, 1)                     # 转成二维才能 fit_transform
).ravel()                                                 # 再扁平为一维

# 注意：测试集必须用同一个 scaler_y 进行 transform，不能重新 fit
data_y_test_scaled = scaler_y.transform(
    data_y_test.values.reshape(-1, 1)
).ravel()

# ========= 6. 将特征转换成 numpy 数组，便于 SVR 训练 =========
X_train = data_x_train.values
X_test  = data_x_test.values

# ========= 7. 构建与训练 SVR 模型 =========
svr = SVR(kernel='linear', C=1.0, epsilon=0.2)
svr.fit(X_train, data_y_train_scaled)                      # 用缩放后的 y 训练

# ========= 8. 预测并“反标准化”还原到原尺度 =========
y_pred_scaled = svr.predict(X_test)
y_pred = scaler_y.inverse_transform(
    y_pred_scaled.reshape(-1, 1)
).ravel()

# ========= 9. 计算回归指标（用原始尺度）=========
print("均方误差:", mean_squared_error(data_y_test, y_pred))
print("R2分数:",   r2_score(data_y_test, y_pred))
print("SVR模型训练完成，预测结果如下：")
print(y_pred)