#include<stdio.h>
using namespace std;
const int N=2e5+10;
void fun()
{
    int cnt_0=0,cnt_1=0,cnt_fu1=0,n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        if(x==1) cnt_1++;
        else if(x==-1) cnt_fu1++;
        else cnt_0++;
    }
    if(cnt_fu1%2==1) printf("%d\n",cnt_0+2);
    else printf("%d\n",cnt_0);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}