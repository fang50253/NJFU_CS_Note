#include<iostream>
#include<queue>
#include<unordered_set>
typedef long long ll;
using namespace std;
int bfs(int x,int y,int k)
{
    if(x==y)return 0;
    unordered_set<int>st;
    queue<pair<int,int>>q;
    q.push({x,0});
    st.insert(x);
    while(!q.empty())
    {
        int value=q.front().first;
        int steps=q.front().second;
        q.pop();
        for(int a=1;a<=k;++a)
        {
            ll mul=value*a;
            if(mul==y)return steps+1;
            if(mul<=2e6&&st.find(mul)==st.end())
            {
                st.insert(mul);
                q.push({(int)mul,steps+1});
            }
            if(a!=0&&value%a==0)
            {
                int div=value/a;
                if(div==y)return steps+1;
                if(st.find(div)==st.end())
                {
                    st.insert(div);
                    q.push({div,steps+1});
                }
            }
        }
    }
    return -1;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        printf("%d\n",bfs(x,y,k));
    }
    return 0;
}