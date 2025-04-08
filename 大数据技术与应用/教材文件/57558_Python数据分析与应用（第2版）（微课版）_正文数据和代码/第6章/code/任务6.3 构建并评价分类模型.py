# 代码6-10
import pandas as pd
# 读取数据集
quit_job = pd.read_csv('../data/quit_job.csv', encoding='gbk')
# 拆分数据和标签
quit_job_data = quit_job.iloc[:, :-1]
quit_job_target = quit_job.iloc[:, -1]
# 划分训练集和测试集
from sklearn.model_selection import train_test_split
quit_job_data_train, quit_job_data_test, \
quit_job_target_train, quit_job_target_test = \
train_test_split(quit_job_data, quit_job_target, 
                 test_size=0.2, random_state=66)
# 标准化数据集
from sklearn.preprocessing import StandardScaler 
stdScale = StandardScaler().fit(quit_job_data_train) 
quit_job_trainScaler = stdScale.transform(quit_job_data_train)
quit_job_testScaler = stdScale.transform(quit_job_data_test)
# 构建SVM模型,并预测测试集结果
from sklearn.svm import SVC 
svm = SVC().fit(quit_job_trainScaler, quit_job_target_train)
# 预测训练集结果
quit_job_target_pred = svm.predict(quit_job_testScaler)
print('预测前20个结果为：\n', quit_job_target_pred[: 20])



# 代码6-11
import numpy as np
# 求出预测和真实一样的数目
true = np.sum(quit_job_target_pred == quit_job_target_test )
print('预测对的结果数目为：', true)
print('预测错的结果数目为：', quit_job_target_test.shape[0] - true)
print('预测结果准确率为：', true / quit_job_target_test.shape[0])


# 代码6-12
from sklearn.metrics import accuracy_score,precision_score, \
recall_score,f1_score,cohen_kappa_score
print('使用SVM预测quit_job数据的准确率为：',
      accuracy_score(quit_job_target_test, quit_job_target_pred))
print('使用SVM预测quit_job数据的精确率为：',
      precision_score(quit_job_target_test, quit_job_target_pred))
print('使用SVM预测quit_job数据的召回率为：',
      recall_score(quit_job_target_test, quit_job_target_pred))
print('使用SVM预测quit_job数据的F1值为：',
      f1_score(quit_job_target_test, quit_job_target_pred))
print('使用SVM预测quit_job数据的Cohen’s Kappa系数为：',
      cohen_kappa_score(quit_job_target_test, 
                        quit_job_target_pred))



# 代码6-13
from sklearn.metrics import classification_report
print('使用SVM预测customer数据的分类报告为：', '\n', 
      classification_report(quit_job_target_test, 
                            quit_job_target_pred))


# 代码6-14
from sklearn.metrics import roc_curve
import matplotlib.pyplot as plt
# 求出ROC曲线的x轴和y轴
fpr, tpr, thresholds = \
roc_curve(quit_job_target_test, quit_job_target_pred)
plt.figure(figsize=(10, 6))
plt.xlim(0, 1)  # 设定x轴的范围
plt.ylim(0.0, 1.1)  # 设定y轴的范围
plt.xlabel('False Postive Rate')
plt.ylabel('True Postive Rate')
plt.plot(fpr, tpr, linewidth=2, linestyle='-', color='red')
plt.plot([0, 1], [0, 1], linestyle='-.', color='blue')
plt.savefig('../tmp/ROC曲线.jpg', dpi=1080) 
plt.show()

