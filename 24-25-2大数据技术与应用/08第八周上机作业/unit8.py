import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.decomposition import PCA

data=pd.read_csv("./shill_bidding.csv",encoding="gbk")

# 输出原始的数据集形状

print("原始数据集的形状:",data.shape)

diabetes_data_train,diabetes_data_test=train_test_split(data,test_size=0.2,random_state=42)

# 输出训练集和测试集的形状
print("训练集的形状:",diabetes_data_train.shape)
print("测试集的形状:",diabetes_data_test.shape)

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





