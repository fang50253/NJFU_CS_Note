#include<stdio.h>
#include<map>
using std::map;
void fun()
{
    map<int,int>mp;
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        mp[x]=i;
    }
    if(mp.size()!=n)
    {
        for(int i=1;i<=n;++i)
        {
            if(mp.find(i)==mp.end())
            {
                printf("? %d %d\n",i,i>=2?i-1:i+1);
                fflush(stdout);
                int x;
                scanf("%d",&x);
                if(x==0) printf("! A\n");
                else printf("! B\n");
                fflush(stdout);
                return;
            }
        }
    }
    else
    {
        int x,y;
        printf("? %d %d\n",mp[1],mp[n]);
        fflush(stdout);
        scanf("%d",&x);
        printf("? %d %d\n",mp[n],mp[1]);
        fflush(stdout);
        scanf("%d",&y);
        if(x+y<2*n-2) printf("! A\n");
        else printf("! B\n");
        fflush(stdout);
        return;
    }
}   
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}