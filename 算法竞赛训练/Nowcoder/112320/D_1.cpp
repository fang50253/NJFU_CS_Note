#include<bits/stdc++.h>
using namespace std;
stack<int>sta;
void dfs(int n,int k)
{
    if(n==0)
    {
        //输出
        stack<int>sta2;
        while(sta.size())
        {
            sta2.push(sta.top());
            sta.pop();
        }
        while(sta2.size())
        {
            printf("%d ",sta2.top());
            sta.push(sta2.top());
            sta2.pop();
        }
        printf("\n");
        return;
    }
    for(int i=1;i<=n;++i)
    {
        if(i==k) continue;
        sta.push(i);
        dfs(n-i,i);
        sta.pop();
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    dfs(n,0);
    return 0;
}