#include<stdio.h>
#include<iostream>
#include<vector>
#include<math.h>
#include<queue>
using namespace std;
const int N=2e5+0;
struct NUM
{
    int ori;//存储着原始数据
    int t;//存储位置
};
void fun()
{
    int n;
    scanf("%d",&n);
    vector<vector<NUM>>vec(5);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        vec[x%4].push_back({x,i});
    }
    //先把所有的4的倍数给吐出来
    queue<int>que;
    for(auto x:vec[0]) que.push(x.t);
    int sum=0;
    //printf("%d,%d,%d\n",vec[1].size(),vec[2].size(),vec[3].size());
    while(vec[1].size()!=0||vec[2].size()!=0||vec[3].size()!=0)
    {
        //首先检查剩余的数量
        if(sum==0)
        {
            if(vec[3].size())
            {
                que.push(vec[3].back().t);
                sum+=vec[3].back().ori;
                vec[3].pop_back();
            }
            else if(vec[2].size())
            {
                que.push(vec[2].back().t);
                sum+=vec[2].back().ori;
                vec[2].pop_back();
            }
            else
            {
                printf("-1\n");
                return;
            }
        }
        else if(sum==2)
        {
            if(vec[1].size())
            {
                que.push(vec[1].back().t);
                sum+=vec[1].back().ori;
                vec[1].pop_back();
            }
            else if(vec[2].size())
            {
                que.push(vec[2].back().t);
                sum+=vec[2].back().ori;
                vec[2].pop_back();
            }
            else
            {
                printf("-1\n");
                return;
            }
        }
        else if(sum==3)
        {
            if(vec[3].size())
            {
                que.push(vec[3].back().t);
                sum+=vec[3].back().ori;
                vec[3].pop_back();
            }
            else if(vec[1].size())
            {
                que.push(vec[1].back().t);
                sum+=vec[1].back().ori;
                vec[1].pop_back();
            }
            else
            {
                printf("-1\n");
                return;
            }
        }
        sum%=4;
    }
    while(que.size())
    {
        printf("%d ",que.front());
        que.pop();
    }
    printf("\n");
    return;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}