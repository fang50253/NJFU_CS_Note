#include<stdio.h>
using namespace std;
const int N=2e5+10;
int arr[N];
void fun()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&arr[i]);
    }
    int l=1,r=n,idx=1;
    while(l<r)
    {
        if(idx==arr[l]) ++l;
        else if(idx==arr[r]) --r;
        else {printf("No\n");return;}
        ++idx;
    }
    printf("Yes\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}