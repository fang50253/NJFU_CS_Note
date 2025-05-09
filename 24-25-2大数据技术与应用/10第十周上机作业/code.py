import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
import matplotlib
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

data=pd.read_csv('./shill_bidding.csv',encoding='gbk')
print(data.info())
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']
matplotlib.rcParams['axes.unicode_minus'] = False

# 1.对竞标行为的数据集进行训练集和测试集的划分
X = data.drop('类别', axis=1)
y = data['类别']
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 2.对竞标者的行为进行预测，构建线性回归模型
model = LinearRegression()
model.fit(X_train, y_train)
y_pred = model.predict(X_test)
y_pred_class = (y_pred >= 0.5).astype(int)
y_test_class = (y_test >= 0.5).astype(int)
conf_matrix = confusion_matrix(y_test_class, y_pred_class)
print(conf_matrix)
disp = ConfusionMatrixDisplay(confusion_matrix=conf_matrix, display_labels=['低倾向', '高倾向'])
disp.plot(cmap='Blues')
plt.title('混淆矩阵')
plt.savefig("混淆矩阵.png")

# 3.计算绝对误差，均方误差和R2分数
mae = mean_absolute_error(y_test, y_pred)
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)
print(f"Mean Absolute Error: {mae:.4f}")
print(f"Mean Squared Error: {mse:.4f}")
print(f"R2 Score: {r2:.4f}")