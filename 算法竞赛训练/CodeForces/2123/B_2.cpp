#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<math.h>
using namespace std;
const int N=2e5+10;
int arr[N],n,m,k;
void fun()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    int maxnum=-1e9;
    for(int i=1;i<=n;++i) maxnum=max(maxnum,arr[i]);
    if(k>1) printf("Yes\n");
    else if(arr[m]==maxnum) printf("Yes\n");
    else printf("No\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return  0;
}