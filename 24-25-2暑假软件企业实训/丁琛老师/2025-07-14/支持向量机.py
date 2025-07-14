# 导入必要的库
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
 
# 加载鸢尾花数据集
iris = load_iris()
X = iris.data
y = iris.target
 
# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)
 
# 特征缩放
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)
 
# 创建SVM分类器
svm_classifier = SVC(kernel='linear', random_state=42)  # 使用线性核
 
# 训练模型
svm_classifier.fit(X_train, y_train)
 
# 进行预测
y_pred = svm_classifier.predict(X_test)
 
# 评估模型
accuracy = accuracy_score(y_test, y_pred)
print(f'Accuracy: {accuracy}')
print('Classification Report:')
print(classification_report(y_test, y_pred))
print('Confusion Matrix:')
print(confusion_matrix(y_test, y_pred))