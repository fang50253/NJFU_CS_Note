from sklearn.datasets import fetch_20newsgroups
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.pipeline import make_pipeline
 
# 加载数据集
categories = ['alt.atheism', 'soc.religion.christian', 'comp.graphics', 'sci.med']
data = fetch_20newsgroups(subset='all', categories=categories)
 
# 创建管道，包括文本向量化（计数）和朴素贝叶斯分类器
model = make_pipeline(CountVectorizer(), MultinomialNB())
 
# 划分数据集为训练集和测试集
X_train, X_test, y_train, y_test = data.data[:3000], data.data[3000:], data.target[:3000], data.target[3000:]
 
# 训练模型
model.fit(X_train, y_train)
 
# 预测测试集
y_pred = model.predict(X_test)
 
# 计算准确率
from sklearn.metrics import accuracy_score
print("Accuracy:", accuracy_score(y_test, y_pred))