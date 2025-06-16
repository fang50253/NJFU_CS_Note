#include<stdio.h>
#include<iostream>
using namespace std;
const int N=1e6+10;
const int M=1e5+10;
const int MOD=998244353;
int arr[N],n,prime[M],cnt,maxi=0;
bool st[N];
void getprimes(int n)
{
    for(int i=2;i<=n;++i)
    {
        if(st[i]) continue;
        prime[cnt++]=i;
        for(int j=i+i;j<=n;j+=i) st[j]=1;
    }
}
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
int lcm(int a,int b)
{
    return a/gcd(a,b)*b;
}
int qmi(int m,int k,int p)
{
    int res=1%p,t=m;
    while(k)
    {
        if(k&1) res=res*t%p;
        t=t*t%p;
        k>>=1;
    }
    return res;
}
int main()
{
    scanf("%d",&n);
    getprimes(1e6);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    vector<vector<int>>vec(1e6);
    //对arr[i]分解质因数
    for(int i=2;i<=n;++i)
    {
        if(arr[i]%i==0)
        {
            int s=0;
            while(arr[i]%i==0) arr[i]/=i,s++;
            vec[i].push_back(s);
            maxi=max(maxi,i);
        }
        if(arr[i]>1)
        {
            vec[arr[i]].push_back(1);
            maxi=max(maxi,arr[i]);
        }
    }
    for(int i=1;i<=maxi;++i) sort(vec[i].begin(),vec[i].end(),greater<int>());
    int ans=0;
    for(int i=1;i<=n;++i)
    {
        int res=0;
        for(int j=0;j<=vec[i].size();++j)
        {
            res+=vec[i][j]*qmi(i,j,MOD);
        }
        ans+=res;
    }
    printf("%d\n",ans);
    return 0;
}