#include<bits/stdc++.h>
using namespace std;
void fun()
{
    
    int n;
    scanf("%d",&n);
    vector<int>vec(n+10);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++vec[x];
    }
    int ans=0;
    for(int i=0;i<=n;++i)
    {
        if(vec[i]>i) ans+=vec[i]-i;
        else if(vec[i]==i) continue;
        else ans+=vec[i]; 
    }
    printf("%d\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}