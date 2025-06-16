#include<stdio.h>
using namespace std;
int dfs(int n,int x,int m)
{
    if(x==1) return n>=m;
    if(n<x) return 0;
    int sum=0;
    for(int i=m;x+i<=n;++i) sum+=dfs(n-i,x-1,i);
    return sum;
}
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    printf("%d\n",dfs(n,k,1));
    return 0;
}