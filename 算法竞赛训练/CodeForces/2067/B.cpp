#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<algorithm>
using namespace std;
const int N=2e5+10;
int arr[1100],t[1100];
void fun()
{
    int n;
    memset(arr,0,sizeof arr);
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        ++arr[x];
    }
    for(int i=1;i<=n;++i)
    {
        if(arr[i]>=2)
        {
            arr[i+1]+=arr[i]-2;
            arr[i]=2;
        }
    }
    for(int i=1;i<=n+1;++i)
    {
        if(arr[i]%2==1)
        {
            printf("No\n");
            return;
        }
    }
    printf("Yes\n");
    return;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}