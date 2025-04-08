# 代码6-1
from sklearn.datasets import load_diabetes
diabetes = load_diabetes()  # 将数据集赋值给diabetes变量
print('diabetes数据集的长度为：', len(diabetes))
print('diabetes数据集的类型为：', type(diabetes))



# 代码6-2
diabetes_data = diabetes['data']
print('diabetes数据集的数据为：','\n', diabetes_data)
diabetes_target = diabetes['target']  # 取出数据集的标签
print('diabetes数据集的标签为：\n', diabetes_target)
diabetes_names = diabetes['feature_names']  # 取出数据集的特征名
print('diabetes数据集的特征名为：\n', diabetes_names)
diabetes_desc = diabetes['DESCR']  # 取出数据集的描述信息
print('diabetes数据集的描述信息为：\n', diabetes_desc)



# 代码6-3
print('原始数据集数据的形状为：', diabetes_data.shape)
print('原始数据集标签的形状为：', diabetes_target.shape)
from sklearn.model_selection import train_test_split
diabetes_data_train, diabetes_data_test, \
diabetes_target_train, diabetes_target_test = \
train_test_split(diabetes_data, diabetes_target, \
                 test_size=0.2, random_state=42) 
print('训练集数据的形状为：', diabetes_data_train.shape)
print('训练集标签的形状为：', diabetes_target_train.shape)
print('测试集数据的形状为：', diabetes_data_test.shape)
print('测试集标签的形状为：', diabetes_target_test.shape)



# 代码6-4
import numpy as np
from sklearn.preprocessing import MinMaxScaler
Scaler = MinMaxScaler().fit(diabetes_data_train)  # 生成规则
# 将规则应用于训练集
diabetes_trainScaler = Scaler.transform(diabetes_data_train) 
# 将规则应用于测试集
diabetes_testScaler = Scaler.transform(diabetes_data_test) 
print('离差标准化前训练集数据的最小值为：', 
      np.min(diabetes_data_train))
print('离差标准化后训练集数据的最小值为：', 
      np.min(diabetes_trainScaler))
print('离差标准化前训练集数据的最大值为：', 
      np.max(diabetes_data_train))
print('离差标准化后训练集数据的最大值为：', 
      np.max(diabetes_trainScaler))
print('离差标准化前测试集数据的最小值为：', 
      np.min(diabetes_data_test))
print('离差标准化后测试集数据的最小值为：', 
      np.min(diabetes_testScaler))
print('离差标准化前测试集数据的最大值为：', 
      np.max(diabetes_data_test))
print('离差标准化后测试集数据的最大值为：', 
      np.max(diabetes_testScaler))



# 代码6-5
from sklearn.decomposition import PCA
pca_model = PCA(n_components=8).fit(diabetes_trainScaler) 
# 将规则应用于训练集
diabetes_trainPca = pca_model.transform(diabetes_trainScaler) 
# 将规则应用于测试集
diabetes_testPca = pca_model.transform(diabetes_testScaler) 
print('PCA降维前训练集数据的形状为：', diabetes_trainScaler.shape)
print('PCA降维后训练集数据的形状为：', diabetes_trainPca.shape)
print('PCA降维前测试集数据的形状为：', diabetes_testScaler.shape)
print('PCA降维后测试集数据的形状为：', diabetes_testPca.shape)
