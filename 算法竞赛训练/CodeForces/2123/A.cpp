#include<stdio.h>
using namespace std;
void fun()
{
    int n;
    scanf("%d",&n);
    if(n%4==0) printf("Bob\n");
    else printf("Alice\n");
}
int main ()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}