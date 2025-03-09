import numpy as np
a=np.array([[1,2,3,4,5,6]])
for i in range(0,6):
    b=np.roll(a[i],1)
    # print(list(b))
    a=np.vstack((a,b))
print(a)