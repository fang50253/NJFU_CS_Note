#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<cmath>
#include<utility>
#include<unordered_map>
#include<queue>
#include<stack>
#include<cstdlib>
#include<string.h>
#include<stdlib.h>
#include<unordered_set>
#define PII pair<int,int>
using namespace std;
typedef long long ll;
const int N=2e5+10;
int arr[N],n,k;
void fun()
{
    scanf("%d%d",&n,&k);
    priority_queue<int>que;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&arr[i]);
        que.push(arr[i]);
    }
    int t=1,ans=0;
    while(que.size())
    {
        //printf("%d ",que.top());
        auto x=t*que.top();
        que.pop();
        if(x<=k) t*=2;
        else ++ans;
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