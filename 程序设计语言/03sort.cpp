#include<stdio.h>
int a[110],n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=n;++i)
    {
        for(int j=2;j<=n;++j)
        {
            if(a[j]<a[j-1])
            {
                //对a[j]和a[j-1]交换
                int tmp=a[j];
                a[j]=a[j-1];
                a[j-1]=tmp;
            }
        }
    }
    for(int i=1;i<=n;++i) printf("%d ",a[i]);
    return 0;
}