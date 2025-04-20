import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.preprocessing import LabelEncoder, MinMaxScaler, StandardScaler
import numpy as np
import matplotlib.pyplot as plt
from sklearn.svm import SVC
from sklearn.decomposition import PCA
from sklearn.model_selection import train_test_split
from sklearn.feature_selection import chi2

# 构造一个示例 DataFrame（你可以用真实数据替换）
data = {
    "Name": ["Alice", "Bob", "Charlie", "David"],
    "Age": [29, 34, 42, 23],
    "Gender": ["F", "M", "M", "M"],
    "Blood Type": ["A", "B", "O", "AB"],
    "Medical Condition": ["Diabetes", "Hypertension", "Asthma", "Healthy"],
    "Date of Admission": ["2024-01-01", "2024-02-14", "2024-03-20", "2024-04-05"],
    "Doctor": ["Dr. A", "Dr. B", "Dr. C", "Dr. A"],
    "Hospital": ["Hospital X", "Hospital Y", "Hospital X", "Hospital Y"],
    "Insurance Provider": ["Insure1", "Insure2", "Insure1", "Insure2"],
    "Billing Amount": [2000, 3500, 1800, 2400],
    "Room Number": [101, 202, 303, 404],
    "Admission Type": ["Emergency", "Routine", "Emergency", "Routine"],
    "Discharge Date": ["2024-01-10", "2024-02-20", "2024-03-28", "2024-04-12"],
    "Medication": ["MedA", "MedB", "MedA", "MedC"],
    "Test Results": [75.5, 88.0, 90.5, 65.0],
    "Length of Stay": [9, 6, 8, 7]
}

df = pd.DataFrame(data)

# 将日期转换为 datetime 类型
df["Date of Admission"] = pd.to_datetime(df["Date of Admission"])
df["Discharge Date"] = pd.to_datetime(df["Discharge Date"])

# 可以提取时间差（天数）作为特征替代 Length of Stay（可选）
df["Stay Days"] = (df["Discharge Date"] - df["Date of Admission"]).dt.days

# 对非数值字段进行编码（仅针对相关性分析，不改变原始数据）
df_encoded = df.copy()

for col in df_encoded.columns:
    if df_encoded[col].dtype == 'object':
        df_encoded[col] = pd.factorize(df_encoded[col])[0]

# 计算相关系数矩阵
corr = df_encoded.corr()
print(corr)

# 画热力图
plt.figure(figsize=(14, 10))
sns.heatmap(corr, annot=True, cmap="coolwarm", fmt=".2f", linewidths=0.5)
plt.title("Correlation Matrix")
plt.tight_layout()
plt.savefig("相关系数矩阵_Correlation_Matrix.png")
plt.show()


from sklearn.model_selection import train_test_split

# 划分数据集，0.2 用于测试
train_data, test_data = train_test_split(df_encoded, test_size=0.2, random_state=42)

# 输出划分后的数据集大小
print(f"训练集大小: {train_data.shape}")
print(f"测试集大小: {test_data.shape}")


# 构造示例数据（可替换为你的真实数据）
data = {
    "Age": [29, 34, 42, 23, 30, 50, 28],
    "Gender": ["F", "M", "M", "M", "F", "F", "M"],
    "Blood Type": ["A", "B", "O", "AB", "A", "O", "B"],
    "Medical Condition": ["Diabetes", "Hypertension", "Asthma", "Healthy", "Diabetes", "Healthy", "Hypertension"],
    "Billing Amount": [2000, 3500, 1800, 2400, 2200, 3000, 2700],
    "Test Results": [75.5, 88.0, 90.5, 65.0, 80.0, 72.5, 78.0],
    "Length of Stay": [9, 6, 8, 7, 10, 5, 6]
}

df = pd.DataFrame(data)

# 选择用于训练的特征
features = ["Age", "Billing Amount", "Test Results", "Length of Stay", "Gender", "Blood Type"]
X = df[features]

# 编码分类特征
for col in ["Gender", "Blood Type"]:
    le = LabelEncoder()
    X.loc[:, col] = le.fit_transform(X[col])

# 提取标签
y = df["Medical Condition"]
label_encoder = LabelEncoder()
y_encoded = label_encoder.fit_transform(y)  # 转换为数字

# 标准化
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# PCA 降维
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_scaled)

# SVM 分类器
clf = SVC(kernel='rbf', gamma='auto')
clf.fit(X_pca, y_encoded)

# 画决策边界
def plot_decision_boundary(X, y, clf, title):
    h = .02
    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h),
                         np.arange(y_min, y_max, h))
    Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)

    plt.figure(figsize=(10, 6))
    plt.contourf(xx, yy, Z, cmap=plt.cm.coolwarm, alpha=0.6)
    scatter = plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.coolwarm, edgecolors='k')
    plt.xlabel("PCA Component 1")
    plt.ylabel("PCA Component 2")
    plt.title(title)

    # 修复 legend 报错问题
    handles, _ = scatter.legend_elements()
    labels = label_encoder.classes_

    # 转换 labels 为 list，防止 numpy array 导致 ValueError
    labels = list(labels)

    if len(handles) == len(labels):
        plt.legend(handles=handles, labels=labels)
    else:
        plt.legend()

    plt.tight_layout()
    plt.savefig("SVM_PCA_Decision_Boundary.png")
    plt.show()

# 绘图
plot_decision_boundary(X_pca, y_encoded, clf, "SVM with PCA - Medical Condition Classification")

# 假设你已经有了 PCA 对象和列名
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_scaled)

# 打印每个主成分对原始特征的贡献
component_df = pd.DataFrame(
    data=np.round(pca.components_, 4),
    columns=X.columns,
    index=['PCA Component 1', 'PCA Component 2']
)

print("📌 每个主成分由哪些特征组成：")
print(component_df.T.sort_values(by='PCA Component 1', ascending=False))  # 可以排序查看贡献度


import matplotlib.pyplot as plt

# 画主成分权重条形图
for i in range(pca.components_.shape[0]):
    plt.figure(figsize=(8, 4))
    plt.bar(X.columns, pca.components_[i])
    plt.title(f"PCA Component {i+1} - Feature Contributions")
    plt.xticks(rotation=45)
    plt.ylabel("Weight")
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"PCA_Component_{i+1}_Feature_Contributions.png")
    plt.show()


# 2. 分离特征和目标
X = df.drop(columns=["Medical Condition"])
y = df["Medical Condition"]

# 3. 对 X 中的分类变量编码，保持非负
for col in X.columns:
    if X[col].dtype == "object":
        X[col] = LabelEncoder().fit_transform(X[col])

# 4. 归一化（卡方检验要求非负）
X_scaled = MinMaxScaler().fit_transform(X)

# 5. 进行卡方检验
chi_scores, p_values = chi2(X_scaled, y)

# 6. 整理结果为 DataFrame
chi2_result = pd.DataFrame({
    "Feature": X.columns,
    "Chi2 Score": chi_scores,
    "p-value": p_values
}).sort_values(by="Chi2 Score", ascending=False)

# 7. 打印结果
print(chi2_result)