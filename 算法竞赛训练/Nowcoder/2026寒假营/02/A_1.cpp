#include<bits/stdc++.h>
using namespace std;
void fun()
{
    int a[3];
    scanf("%d%d%d",&a[0],&a[1],&a[2]);
    sort(a,a+3);
    if(a[2]-a[0]>=2) printf("NO\n");
    else printf("YES\n");
}
int main()
{
    int n;
    scanf("%d",&n);
    while(n--) fun();
    return 0;
}