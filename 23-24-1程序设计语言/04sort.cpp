#include<stdio.h>
void sort(int q[],int len)
{
    for(int i=1;i<=len;++i)
    {
        for(int j=2;j<=len;++j)
        {
            if(q[j]<q[j-1])
            {
                //对a[j]和a[j-1]交换
                int tmp=q[j];
                q[j]=q[j-1];
                q[j-1]=tmp;
            }
        }
    }
}
int main()
{
    int n,a[110];
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    sort(a,n);
    for(int i=1;i<=n;++i) printf("%d ",a[i]);
    return 0;
}