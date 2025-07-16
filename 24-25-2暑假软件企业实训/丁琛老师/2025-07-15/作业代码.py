from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
from sklearn.multiclass import OneVsOneClassifier
from sklearn.metrics import classification_report

# 加载鸢尾花数据集
iris = datasets.load_iris()
X = iris.data
y = iris.target

# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# 使用一对一策略
ovo_clf = OneVsOneClassifier(SVC(kernel='linear'))
ovo_clf.fit(X_train, y_train)

# 预测和评估
y_pred_ovo = ovo_clf.predict(X_test)
print("一对一策略分类结果：")
print(classification_report(y_test, y_pred_ovo, target_names=iris.target_names))


from sklearn.multiclass import OneVsRestClassifier

# 使用一对多策略
ovr_clf = OneVsRestClassifier(SVC(kernel='linear'))
ovr_clf.fit(X_train, y_train)

# 预测和评估
y_pred_ovr = ovr_clf.predict(X_test)
print("一对多策略分类结果：")
print(classification_report(y_test, y_pred_ovr, target_names=iris.target_names))