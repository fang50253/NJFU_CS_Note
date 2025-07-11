#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
void fun()
{
    int a,b;
    scanf("%d%d",&a,&b);
    int c=gcd(a,b);
    if(a+b>c&&a+c>b&&b+c>a) printf("Yes\n");
    else printf("No\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}