import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

# 读入文件

print(os.getcwd())

score=pd.read_excel("./第六周上机作业/student_grade.xlsx")

print(score)

# 实现步骤1

plt.figure(figsize=(6,6))