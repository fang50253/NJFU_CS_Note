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
int arr[N],sub[N];
void fun()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    k=arr[k];
    sort(arr+1,arr+1+n);
    int l=1;
    for(int i=1;i<=n;++i)
    {
        if(arr[i]==k) l=i;
    }
    //printf("%d %d\n",l,arr[l]);
    //构建差分数组sub
    for(int i=1;i<=n;++i) sub[i-1]=arr[i]-arr[l];
    for(int i=l;i<=n-1;++i)
    {
        if(sub[i]>=arr[i]+1)
        {
            //printf("%d\n",i);
            printf("NO\n");
            return;
        }
    }
    printf("YES\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}