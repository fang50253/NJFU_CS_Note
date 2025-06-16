#include<stdio.h>
#include<iostream>
#include<unordered_set>
#include<vector>
#include<unordered_map>
using namespace std;
const int N=1e6+10;
int t[N];//表示鸽子i的位置
int main()
{
    int n,q,ans=0;
    scanf("%d%d",&n,&q);
    vector<unordered_set<int>>s(n+1);
    //init
    for(int i=1;i<=n;++i)
    {
        s[i].insert(i);
        t[i]=i;
    }
    while(q--)
    {
        int op;
        scanf("%d",&op);
        if(op==1)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            if(s[t[a]].size()==2) --ans;
            s[t[a]].erase(a);
            t[a]=b;
            s[b].insert(a);
            if(s[b].size()==2) ++ans;
        }
        else if(op==2)
        {
            printf("%d\n",ans);
        }
    }
    return 0;
}