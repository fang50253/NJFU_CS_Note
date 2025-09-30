#include<stdio.h>
using namespace std;
void fun()
{
    int a,b;
    scanf("%d%d",&a,&b);
    if(b%2==1) printf("%d\n",a);
    else printf("0\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}