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
bool judge(int x) {
    if(x+k-1>n) return 0;
    for(int i=x;i<x+k;++i)
    {
        if(arr[i]==1) return 0;
    }
    return 1;
}
void fun()
{
    int ans=0;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    for(int i=1;i<=n;)
    {
        if(judge(i)) 
        {
            ++ans;
            i+=k+1;
        }
        else ++i;
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