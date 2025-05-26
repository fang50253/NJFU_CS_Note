import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt
import matplotlib


plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']
matplotlib.rcParams['axes.unicode_minus'] = False

data=pd.read_csv('./shill_bidding.csv',encoding="gbk")
print(data)

# 对数据进行训练集和测试集的划分
X = data.iloc[:, :-1]
y = data.iloc[:, -1]
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 对竞标着的竞标行为进行类别判断
def label_bidder(row):
    value = row['竞标者倾向']
    if value >= 0.6:
        return '高倾向'
    elif value >= 0.2:
        return '中等倾向'
    else:
        return '低倾向'
X_train['类别'] =X_train.apply(label_bidder,axis=1)


X_train['类别'] = X_train.apply(label_bidder, axis=1)
X_test['类别'] = X_test.apply(label_bidder, axis=1)


# 输出竞标行为分析
def analyze_bidder_behavior(data):
    bidder_behavior = data.groupby('类别').agg({
        '竞标比率': ['mean', 'std'],
        '连续竞标': ['mean', 'std'],
        '上次竞标': ['mean', 'std']
    })
    return bidder_behavior
bidder_behavior = analyze_bidder_behavior(X_train)
print(bidder_behavior)

# 构建支持向量机模型
from sklearn.svm import SVC
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler
# 标准化数据
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train.drop('类别', axis=1))
X_test_scaled = scaler.transform(X_test.drop('类别', axis=1))
# 创建支持向量机模型
svm_model = SVC(kernel='linear', random_state=42)
# 训练模型
svm_model.fit(X_train_scaled, y_train)
# 预测
y_pred = svm_model.predict(X_test_scaled)
# 输出分类报告
print(classification_report(y_test, y_pred))
# 输出混淆矩阵
conf_matrix = confusion_matrix(y_test, y_pred)
print(conf_matrix)
# 可视化混淆矩阵
import seaborn as sns
plt.figure(figsize=(8, 6))
sns.heatmap(conf_matrix, annot=True, fmt='d', cmap='Blues', xticklabels=['低倾向', '中等倾向', '高倾向'], yticklabels=['低倾向', '中等倾向', '高倾向'])
plt.xlabel('预测类别')
plt.ylabel('真实类别')
plt.title('混淆矩阵')
plt.savefig("混淆矩阵.jpg")

# 检查 SVM 模型的特征权重（仅适用于线性核）
if svm_model.kernel == 'linear':
    feature_importance = svm_model.coef_[0]
    feature_names = X_train.drop('类别', axis=1).columns
    importance_df = pd.DataFrame({
        '特征': feature_names,
        '权重': feature_importance
    }).sort_values(by='权重', key=abs, ascending=False)
    print("SVM 模型特征重要性：")
    print(importance_df)

    # 可视化特征重要性
    plt.figure(figsize=(10, 6))
    sns.barplot(x='权重', y='特征', data=importance_df, hue=None, legend=False)
    plt.title('SVM 模型特征重要性')
    plt.xlabel('权重')
    plt.ylabel('特征')
    plt.savefig("SVM特征重要性.jpg")
else:
    print("非线性核 SVM 无法直接获取特征重要性。")

# 打印分类模型评价方法，评价分类模型性能
def evaluate_classification_model(y_true, y_pred):
    accuracy = np.mean(y_true == y_pred)
    precision = np.sum((y_true == 1) & (y_pred == 1)) / np.sum(y_pred == 1)
    recall = np.sum((y_true == 1) & (y_pred == 1)) / np.sum(y_true == 1)
    f1_score = 2 * (precision * recall) / (precision + recall)
    return accuracy, precision, recall, f1_score
accuracy, precision, recall, f1_score = evaluate_classification_model(y_test, y_pred)
print(f"准确率: {accuracy:.2f}")
print(f"精确率: {precision:.2f}")
print(f"召回率: {recall:.2f}")
print(f"F1 分数: {f1_score:.2f}")
# 可视化数据
def visualize_data(X, y):
    for i in range(3,7):

        plt.figure(figsize=(10, 6))
        plt.scatter(X.iloc[:, 2], X.iloc[:, i], c=y, cmap='viridis', edgecolor='k', s=50)
        plt.title('数据可视化')
        # plt.xlabel('特征 1')
        # plt.ylabel('特征 2')
        plt.xlabel(X.columns[2])
        plt.ylabel(X.columns[i])
        plt.savefig(f"数据可视化{i}.jpg")
# 可视化数据
plt.figure(figsize=(10, 6))
plt.scatter(X.iloc[:, 4], X.iloc[:, 9], c=y, cmap='viridis', edgecolor='k', s=50)
plt.title('数据可视化')
plt.xlabel(X.columns[4])
plt.ylabel(X.columns[9])
plt.savefig(f"数据可视化——连续竞标和胜率.jpg")

visualize_data(X_train.drop('类别', axis=1), y_train)
# 主成分分析
pca = PCA(n_components=2)
X_train_pca = pca.fit_transform(X_train.drop('类别', axis=1))
X_test_pca = pca.transform(X_test.drop('类别', axis=1))
# 可视化主成分分析结果
def visualize_pca(X, y):
    plt.figure(figsize=(10, 6))
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap='viridis', edgecolor='k', s=50)
    plt.title('主成分分析结果')
    plt.xlabel('主成分 1')
    plt.ylabel('主成分 2')
    plt.savefig("主成分分析结果.jpg")
# 可视化主成分分析结果
visualize_pca(X_train_pca, y_train)