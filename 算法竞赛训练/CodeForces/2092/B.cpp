#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
const int N=2e5+10;
string a,b;
int cnt[N];//cnt[i]存储的是b中第i个数字以前数字0出现的次数
void fun()
{   
    int n,a0=0,b0=0,a1=0,b1=0;//a0代表a中奇数位置出现0的次数    
    scanf("%d",&n);
    cin>>a>>b;
    for(int i=1;i<=n;++i)
    {
        if(a[i-1]=='0')
        {
            if(i%2==1) ++a0;
            else ++a1;
        }
        if(b[i-1]=='0')
        {
            if(i%2==1) ++b0;
            else ++b1;
        }
    }
    if(a0+b1<n+1>>1||a1+b0<n>>1) printf("No\n");
    else printf("Yes\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}