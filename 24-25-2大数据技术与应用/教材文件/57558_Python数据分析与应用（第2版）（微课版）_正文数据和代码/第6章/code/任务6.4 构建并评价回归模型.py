# 代码6-15
import pandas as pd
# 读取数据集
concrete = pd.read_csv('../data/concrete.csv', encoding='gbk')
# 拆分数据和标签
concrete_data = concrete.iloc[:, :-1]
concrete_target = concrete.iloc[:, -1]
# 划分训练集和测试集
from sklearn.model_selection import train_test_split
concrete_data_train, concrete_data_test, \
concrete_target_train, concrete_target_test = \
train_test_split(concrete_data, concrete_target,
                 test_size=0.2, random_state=20)
from sklearn.linear_model import LinearRegression
concrete_linear = LinearRegression().fit(concrete_data_train, 
                                       concrete_target_train)
# 预测测试集结果    
y_pred = concrete_linear.predict(concrete_data_test)
print('预测前20个结果为：','\n', y_pred[: 20])



# 代码6-16
import matplotlib.pyplot as plt
from matplotlib import rcParams
rcParams['font.sans-serif'] = 'SimHei'
fig = plt.figure(figsize=(12, 6))  # 设定空白画布，并制定大小
plt.plot(range(concrete_target_test.shape[0]), 
         list(concrete_target_test), color='blue')
plt.plot(range(concrete_target_test.shape[0]),
         y_pred, color='red', linewidth=1.5, linestyle='-.')
plt.legend(['真实值', '预测值'])
plt.savefig('../tmp/回归结果.jpg', dpi=1080) 
plt.show()  # 显示图片



# 代码6-17
from sklearn.metrics import explained_variance_score,\
mean_absolute_error, mean_squared_error,\
median_absolute_error, r2_score
print('diabetes数据线性回归模型的平均绝对误差为：',
      mean_absolute_error(concrete_target_test, y_pred))
print('diabetes数据线性回归模型的均方误差为：',
      mean_squared_error(concrete_target_test, y_pred))
print('diabetes数据线性回归模型的中值绝对误差为：',
      median_absolute_error(concrete_target_test, y_pred))
print('diabetes数据线性回归模型的可解释方差值为：',
      explained_variance_score(concrete_target_test, y_pred))
print('diabetes数据线性回归模型的R方值为：',
      r2_score(concrete_target_test, y_pred))
