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
const int N=2e5+10;
int arr[N],n,k;;
int judge(int x)//用于判断x之后的k天里是不是都是晴天
{
    for(int i=x,j=1;j<=k;++i,++j)
    {
        if(arr[i]==1) return j;
        if(i>n) return j;
    }
    return 0;
}
void fun()
{
    int ans=0;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    for(int i=1;i<=n;)
    {
        int t=judge(i);
        if(!t) ++ans,i+=k+1;
        else i+=t+1;
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