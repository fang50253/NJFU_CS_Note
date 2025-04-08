# 代码9-8
import pandas as pd
from sklearn.metrics import confusion_matrix

# 自定义评价函数
def test_pre(pred):
    # 混淆矩阵
    hx = confusion_matrix(y_te, pred, labels=['非流失', '准流失'])
    print('混淆矩阵：\n', hx)
    # 精确率
    P = hx[1, 1] / (hx[0, 1] + hx[1, 1])
    print('精确率：', round(P, 3))
    # 召回率
    R = hx[1, 1] / (hx[1, 0] + hx[1, 1])
    print('召回率：', round(R, 3))
    # F1值
    F1 = 2 * P * R / (P + R)
    print('F1值：', round(F1, 3))

# 读取数据
info_user = pd.read_csv('../tmp/info_user_clear.csv', encoding='gbk')
# 删除流失客户
info_user = info_user[info_user['TYPE'] != '已流失']
model_data = info_user.iloc[:, [1, 2, 3, 4, 5]]
# 划分测试集、训练集
from sklearn.model_selection import train_test_split
x_tr, x_te, y_tr, y_te = train_test_split(model_data.iloc[:, :-1],
                               model_data['TYPE'],
                               test_size=0.2, random_state=12345)
# 构建模型
from sklearn.tree import DecisionTreeClassifier as DTC
dtc = DTC(random_state=12345)
dtc.fit(x_tr, y_tr)  # 训练模型
pre = dtc.predict(x_te)
# 评价模型
test_pre(pre)

print('真实值：\n', y_te[:10].to_list())
print('预测结果：\n', pre[:10])



# 代码9-9
from sklearn.svm import LinearSVC
svc = LinearSVC(random_state=123)
svc.fit(x_tr, y_tr)
pre = svc.predict(x_te)
test_pre(pre)

print('真实值：\n', y_te[:10].to_list())
print('预测结果：\n', pre[:10])
