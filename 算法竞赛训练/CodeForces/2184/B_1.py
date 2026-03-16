n=int(input())
def cal(s,k,m):
    if s<=k:
        top=s
    else:
        if (m//k)%2==0:
            top=s
        else:
            top=k
    if top<m%k:
        return 0
    else:
        return top-m%k
for i in range(n):
    str=input()
    a,b,c=str.split()
    a=int(a)
    b=int(b)
    c=int(c)
    print(cal(a,b,c))