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
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    sort(arr+1,arr+1+n);
    int ans=n;
    int *p=arr+n+1;
    while(k>=1)
    {
        p=upper_bound(arr,p,k)+1;
        if(p==arr+1) break;
        k>>=1;
        --ans;
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