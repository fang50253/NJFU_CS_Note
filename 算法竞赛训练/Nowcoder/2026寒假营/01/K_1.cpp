#include<bits/stdc++.h>
using namespace std;
void fun()
{
    int n;
    scanf("%d",&n);
    if(n==1) printf("YES\n1\n");
    else if(n==3) printf("YES\n1 2 3\n");
    else printf("NO\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}