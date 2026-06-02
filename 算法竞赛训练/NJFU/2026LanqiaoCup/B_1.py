def c(a,b):
    ans=1
    for i in range(b):
        ans=ans*(a-i)
    for i in range(b-1):
        ans=ans//b
    return ans

def cal(n):
    ans=0
    for i in range(2,n):
        ans=ans+2*i*c(n-1,i)
    ans=ans+2*n-1
    return ans


a=int(input())
print(cal(a)%998244353)