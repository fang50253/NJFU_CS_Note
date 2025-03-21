import numpy as np
import pandas as pd
u3data=pd.read_csv("./unit3.csv",encoding='gbk')
print("数据维度"+str(np.ndim(u3data)))
print("数据形状"+str(np.shape(u3data)))
print("特征名称: " + str(u3data.columns.tolist()))
print()
u3row=u3data.index[u3data['房屋类型']=='unit'].tolist()
u3single=u3data.iloc[u3row]
print(u3single)