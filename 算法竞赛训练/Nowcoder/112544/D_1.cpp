#include<stdio.h>
using namespace std;
void fun()
{
    int x,k;
    scanf("%d%d",&x,&k);
    int t=k/x;//前面有几组数据
    int p=k%x;//余数
    if(p==0) printf("%d\n",2*t-1);
    else printf("%d\n",2*t*(x-1)+p*2);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}