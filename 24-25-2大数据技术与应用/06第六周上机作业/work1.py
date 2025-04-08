import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

# 实现步骤1
print(os.getcwd())

plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']

score=pd.read_excel("./第六周上机作业/student_grade.xlsx")

print(score)

# 实现步骤2
bins = [0, 150, 200, 250, 300]
labels = ["不及格", "及格", "良好", "优秀"]

score['等级'] = pd.cut(score['总成绩'], bins=bins, labels=labels, right=False)
score_counts = score['等级'].value_counts().reindex(labels)

plt.figure(figsize=(3, 3))
plt.pie(score_counts, labels=labels, autopct='%1.1f%%', startangle=140, colors=["red", "yellow", "lightblue", "green"])
plt.title("学生成绩分布情况")
plt.savefig('./第六周上机作业/work1_ans/pic1.jpg')
plt.show()

# 实现步骤3

subjects = ["数学成绩", "阅读成绩", "写作成绩"]
score_boxplot_data = score[subjects]

plt.figure(figsize=(3, 3))
plt.boxplot(score_boxplot_data.values, labels=subjects, patch_artist=True, boxprops=dict(facecolor="lightblue"))
plt.title("学生各项考试成绩分布情况")
plt.ylabel("成绩")
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.savefig('./第六周上机作业/work1_ans/pic2.jpg')
plt.show()

# 实现步骤4
score_stats = score[subjects].describe()
print("各项单科成绩的基本统计信息：")
print(score_stats)