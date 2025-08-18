#include<stdio.h>
using namespace std;
void fun()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        if((i&1)==0&&i==n) printf("2 ");
        else if((i&1)==0) printf("3 ");
        else printf("-1 ");
    }
    printf("\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}