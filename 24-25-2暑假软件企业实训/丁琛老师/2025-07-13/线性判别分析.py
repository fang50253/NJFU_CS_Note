from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score

# 加载数据集
data = load_iris()
X = data.data
y = data.target

# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=0)

# 特征缩放（可选，但通常推荐）
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# 创建LDA模型
lda = LinearDiscriminantAnalysis(n_components=2)  # 可以选择降维后的维度数，这里选择2维作为示例
X_train_lda = lda.fit_transform(X_train, y_train)  # 训练并转换训练数据
X_test_lda = lda.transform(X_test)  # 转换测试数据

# 使用降维后的数据进行分类
classifier = LogisticRegression()
classifier.fit(X_train_lda, y_train)
y_pred = classifier.predict(X_test_lda)

# 评估分类性能
accuracy = accuracy_score(y_test, y_pred)
print(f"Accuracy after LDA: {accuracy:.4f}")