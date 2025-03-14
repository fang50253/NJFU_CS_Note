import numpy as np
import pandas as pd

df = pd.DataFrame(
    data=np.arange(12).reshape((4, 3)),
    index=list("ABCD"),
    columns=["aa", "bb", "cc"]
)

print(df)

print(df.describe())