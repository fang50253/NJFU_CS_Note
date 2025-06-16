#include<stdio.h>
using namespace std;
const int N=1e5+10;
void fun()
{
    int x;
    scanf("%d",&x);
    if(x%2==1) printf("Yes\n");
    else printf("No\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}