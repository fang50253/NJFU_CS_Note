import numpy as np
import pandas as pd
df = pd.DataFrame(
    data=np.arange(12).reshape((4, 3)),
    index=list("ABCD"),
    columns=["aa", "bb", "cc"]
)
print(df)

print(df.describe()) # 数据摘要

print(df.T) # 输出转置

df["dd"]=12 # 增加一列dd，设置为12
print(df)

df.drop("A",inplace=True) # 如果不设置inplace，返回值不会被接收
print(df)

df.info()