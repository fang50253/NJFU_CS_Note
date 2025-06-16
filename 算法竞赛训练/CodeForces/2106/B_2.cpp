#include<stdio.h>
#include<string.h>
using namespace std;
void fun()
{
    int n,x;
    scanf("%d%d",&n,&x);
    if(x==0)
    {
        for(int i=n-1;i>=0;--i) printf("%d ",i);
        printf("\n");
    }
    else
    {
        for(int i=0;i<x;++i) printf("%d ",i);
        for(int i=n-1;i>=x;--i) printf("%d ",i);
        printf("\n");
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}