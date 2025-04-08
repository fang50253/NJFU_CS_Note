import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

# 读入文件

print(os.getcwd())

score=pd.read_excel("./第六周上机作业/student_grade.xlsx")

print(score)

# 实现步骤1

plt.figure(figsize=(6,3))

# 实现步骤2

avg1=score.groupby("自我效能感")["总成绩"].mean()
print(str(avg1))
print()

avg2=score.groupby("考试课程准备情况")["总成绩"].mean()
print(str(avg2))

# 实现步骤3

plt.subplot(1, 2, 1)
plt.xlabel("自我效能感")
plt.ylabel("学生总成绩")
plt.bar(avg1.index,avg1.values,width=0.33)
plt.subplot(1, 2, 2)
plt.xlabel("考试课程准备情况")
plt.ylabel("学生总成绩")
plt.bar(avg2.index,avg2.values,width=0.2)
print()
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']

plt.show()

# 实现步骤4

print(avg1.describe())
print()
print(avg2.describe())