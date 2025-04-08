#include<stdio.h>
#define N(x,y) x+y;
int main()
{
    int a=1,b=2;
    int hello=a<b?a:N(a,b);
    //int hello=a<b?a:a+b;
    printf("%d",hello);
    return 0;
}