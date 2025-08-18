#include<stdio.h>
#include<map>
using namespace std;
const int N=2e5+10;
int n,k;
int abs_(int a)
{
    return a>0?a:-a;
}
void fun()
{
    map<int,int>mp;
    bool flag=1;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        x=x%k;
        ++mp[min(x,k-x)];
    }
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        x=x%k;
        --mp[min(x,k-x)];
    }
    for(auto x:mp) 
    {
        if(x.second!=0)
        {
            printf("No\n");
            return;
        }
    }
    printf("Yes\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}