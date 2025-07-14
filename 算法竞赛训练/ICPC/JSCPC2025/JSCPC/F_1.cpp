/*
@fzy50253 2025-06-04
*/
#include<stdio.h>
#include<unordered_map>
#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
const int N=1e5+10;
unordered_map<char,int>mp;
int n,a,b,s;
bool tg[20];//if pass the problem,set it as True
int wa[20];//reject number
struct Node
{
    char ti;
    int time;
    bool operator < (const Node &W) const
    {
        return time>W.time;
    }
};
void fun()
{
    scanf(" %d %d %d %d",&n,&a,&b,&s);
    memset(tg,0,sizeof tg);
    memset(wa,0,sizeof wa);
    int penety_time=0,othertg=0,pdcnt=0;
    priority_queue<Node>pd;
    while(s--)
    {
        int time;
        char ti,zt[10];
        scanf(" %d %c %s",&time,&ti,zt);
        if(tg[mp[ti]]) continue;
        if(strcmp(zt,"ac")==0)
        {
            penety_time+=wa[mp[ti]]*20+time;
            tg[mp[ti]]=1;
            ++othertg;
        }
        else if(strcmp(zt,"rj")==0)
        {
            ++wa[mp[ti]];
        }
        else if(strcmp(zt,"pd")==0)
        {
            pd.push({ti,wa[mp[ti]]*20+time});
        }
    }
    if(othertg>a||(othertg==a&&b>penety_time))
    {
        printf("0\n");
        return;
    }
    while(pd.size())
    {
        auto out=pd.top();
        pd.pop();
        // cout<<out.ti<<" "<<out.time<<endl;
        // cout<<othertg<<" "<<penety_time<<endl;
        if(tg[mp[out.ti]]) continue;
        tg[mp[out.ti]]=1;
        ++othertg;
        penety_time+=out.time;
        ++pdcnt;
        if(othertg>a||(othertg==a&&b>penety_time))
        {
            printf("%d\n",pdcnt);
            return;
        }
    }
    printf("-1\n");
}
int main()
{
    int t;
    for(int i=1,j='A';i<=16;++i,++j) mp[j]=i;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}