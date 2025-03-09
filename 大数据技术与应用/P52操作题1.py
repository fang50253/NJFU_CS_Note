import numpy
a=b=c=d=numpy.diag((1,2,3))
sum=numpy.bmat(([[a, b], [c, d]]))
print(sum)
print()
re=numpy.transpose(sum)
print(re)