#include<stdio.h>
using namespace std;
const int N=2e5+10;
void fun()
{
    int a,b;
    scanf("%d%d",&a,&b);
    if((a-b>=2&&a>=21)||a>=30) printf("Alice\n");
    else if((b-a>=2&&b>=21)||b>=30) printf("Bob\n");
    else printf("Underway\n");
}
int main()
{
    int t=1;
    //scanf("%d",&t);
    while(t--) fun();
    return 0;
}