import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
import os
import seaborn as sns

# 实现步骤1

print(os.getcwd())

score=pd.read_csv("./第六周上机作业/aqi.csv")
print(score)

# 实现步骤2

plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']

color_map=dict(zip(score["质量等级"].unique(),["b","y","r"]))
