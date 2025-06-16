import sys
n=int(input())
data=list(map(int,input().split()))
cnt=[0,0,0,0]
for x in data:
    cnt[x] += 1
def check(x):
    s=0
    s+=cnt[0]*(x%4)
    s+=cnt[1]*((x+1)%4)
    s+=cnt[2]*((x+2)%4)
    s+=cnt[3]*((x+3)%4)
    return s<=x
for i in range(int(5e6)):
    if check(i):
        print(i)
        sys.exit(0)