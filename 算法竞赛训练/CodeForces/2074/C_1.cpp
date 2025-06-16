#include<stdio.h>
using namespace std;
int lowbit(int x)
{
    return x&-x;
}
void fun()
{
    int x;
    scanf("%d",&x);
    if(x==lowbit(x)||x+1==lowbit(x+1)) printf("-1\n");
    else printf("%d\n",x+lowbit(x)*2-4*lowbit(x));
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}