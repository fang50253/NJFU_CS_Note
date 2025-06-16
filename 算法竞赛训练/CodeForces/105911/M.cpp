#include<stdio.h>
using namespace std;
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=0;i<n-k;++i) printf("2");
    for(int i=n-k;i<n;++i) printf("3");
    printf("\n");
    return 0;
}