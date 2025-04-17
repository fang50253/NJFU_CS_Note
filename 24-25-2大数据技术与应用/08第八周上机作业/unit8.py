import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt
import matplotlib
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']
matplotlib.rcParams['axes.unicode_minus'] = False   # 解决负号显示问题
data=pd.read_csv("./shill_bidding.csv",encoding="gbk")

# 输出原始的数据集形状

print("原始数据集的形状:",data.shape)

diabetes_data_train,diabetes_data_test=train_test_split(data,test_size=0.2,random_state=42)

# 输出训练集和测试集的形状
print("训练集的形状:",diabetes_data_train.shape)
print("测试集的形状:",diabetes_data_test.shape)

# 画出竞标者倾向特征值的图
import matplotlib.pyplot as plt
import seaborn as sns
plt.figure(figsize=(10, 6))
sns.histplot(data['记录ID'], bins=30, kde=True)
plt.title('竞标者倾向特征值分布')
plt.xlabel('竞标者倾向特征值')
plt.ylabel('频率')
plt.savefig('./竞标者倾向特征值分布.jpg')


# 竞标比率,连续竞标,上次竞标,竞标量,拍卖起拍,早期竞标,胜率,拍卖持续时间（小时）,类别


# 画出竞标量特征值的图
import matplotlib.pyplot as plt
import seaborn as sns
plt.figure(figsize=(10, 6))
sns.histplot(data['竞标量'], bins=30, kde=True)
plt.title('竞标量特征值分布')
plt.xlabel('竞标量特征值')
plt.ylabel('频率')
plt.savefig('./竞标量特征值分布.jpg')


# 画出胜率特征值的图
import matplotlib.pyplot as plt
import seaborn as sns
plt.figure(figsize=(10, 6))
sns.histplot(data['胜率'], bins=30, kde=True)
plt.title('胜率特征值分布')
plt.xlabel('胜率特征值')
plt.ylabel('频率')
plt.savefig('./胜率特征值分布.jpg')

# 画出竞标量和胜率关系的散点图
import matplotlib.pyplot as plt
import seaborn as sns
plt.figure(figsize=(10, 6))
sns.scatterplot(x=data['竞标量'], y=data['胜率'])
plt.title('竞标量和胜率关系')
plt.xlabel('竞标量')
plt.ylabel('胜率')
plt.savefig('./竞标量和胜率关系.jpg')

# 对竞标行为的数据集和标签进行划分
diabetes_data_train=diabetes_data_train.iloc[:,1:]
diabetes_data_test=diabetes_data_test.iloc[:,1:]
pca_model=PCA(n_components=0.999).fit(diabetes_data_train)
diabetes_trainPca=pca_model.transform(diabetes_data_train)
diabetes_testPca=pca_model.transform(diabetes_data_test)

# 输出降维后的数据集形状
print("降维后的训练集形状:",diabetes_trainPca.shape)
print("降维后的测试集形状:",diabetes_testPca.shape)

# 输出降维后的数据集
print("降维后的训练集数据:\n",diabetes_trainPca)
print("降维后的测试集数据:\n",diabetes_testPca)

# 将降维后的数据保存到CSV文件
diabetes_trainPca_df = pd.DataFrame(diabetes_trainPca)
diabetes_trainPca_df.to_csv('diabetes_trainPca.csv', index=False, header=False)
diabetes_testPca_df = pd.DataFrame(diabetes_testPca)
diabetes_testPca_df.to_csv('diabetes_testPca.csv', index=False, header=False)
