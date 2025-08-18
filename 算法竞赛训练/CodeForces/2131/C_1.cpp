#include<stdio.h>
#include<unordered_map>
using namespace std;
const int N=2e5+10;
int n,k;
int abs_(int a)
{
    return a>0?a:-a;
}
void fun()
{
    unordered_map<int,int>mp;
    bool flag=1;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++mp[x%k];
    }
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        if(!flag) continue;
        int t1=x%k;
        int t2=k-t1;
        if(mp.count(t1))
        {
            --mp[t1];
            if(mp[t1]==0) mp.erase(t1);
        }
        else if(mp.count(t2))
        {
            --mp[t2];
            if(mp[t2]==0) mp.erase(t2);
        }
        else flag=0;
    }
    if(flag==0) printf("No\n");
    else printf("Yes\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}