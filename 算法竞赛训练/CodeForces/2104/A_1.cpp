#include<stdio.h>
using namespace std;
void fun()
{
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    if((a+b+c)%3==0&&3*a<=(a+b+c)&&3*b<=(a+b+c)) printf("YES\n");
    else printf("NO\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}