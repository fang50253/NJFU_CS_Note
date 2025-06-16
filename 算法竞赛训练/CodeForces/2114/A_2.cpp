#include<stdio.h>
#include<math.h>
using namespace std;
void fun()
{
    int n,sq;
    scanf("%d",&n);
    sq=sqrt(n);
    if(sq*sq==n)
    {
        printf("%d %d\n",sq>>1,sq-(sq>>1));
        return;
    }
    else printf("-1\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}