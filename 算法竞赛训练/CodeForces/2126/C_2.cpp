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
int arr[N],tmp[N];

void fun()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    int start=arr[k];
    for(int i=1;i<=n;++i) tmp[i]=arr[i];
    sort(tmp+1,tmp+1+n);
    int l=1;
    for(int i=1;i<=n;++i)
    {
        if(tmp[i]==start) 
        {
            l=i;
            break;
        }
    }
    int cur=0;
    for(int i=l+1;i<=n;++i)
    {
        int cost=tmp[i]-tmp[i-1];
        if(tmp[i-1]-cur<=cost)
        {
            printf("NO\n");
            return;
        }
        cur+=cost;
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