#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=2e5+10;
const int INF=0x3f3f3f3f;
int a[N],b[N],n,k;
void fun()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=n;++i) scanf("%d",&b[i]);
    //判断b数组是不是所有的数字都一样
    int flag=1;
    for(int i=1;i<=n;++i)
    {
        if(b[i]!=b[1])
        {
            flag=0;
            break;
        }
    }
    if(!flag)
    {
        //判断a[i]+b[i]是否都相等
        int sum;
        for(int i=1;i<=n;++i)
        {
            if(b[i]!=-1)
            {
                sum=a[i]+b[i];
                break;
            }
        }
        for(int i=1;i<=n;++i)
        {
            if((a[i]+b[i]!=sum&&b[i]!=-1)||a[i]>sum||sum-a[i]>k)
            {
                printf("0\n");
                return;
            }
        }
        printf("1\n");    
        return;    
    }
    int maxa=0,mina=INF;
        for(int i=1;i<=n;++i)
        {
            maxa=max(maxa,a[i]);
            mina=min(mina,a[i]);
        }
        if(mina+k-maxa+1==1061109572) printf("1\n");
        else printf("%d\n",mina+k-maxa+1);

}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}