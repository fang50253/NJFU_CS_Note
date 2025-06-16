#include<stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    int l=0,r=1e5;
    while(l<r)
    {
        int mid=l+r+1>>1;
        double price=mid*140+mid*35+mid*30;
        price*=1.2;
        //printf("%d:%d\n",mid,price);
        if(price<=n) l=mid;
        else r=mid-1;
    }
    printf("%d\n",l);
    return 0;
}