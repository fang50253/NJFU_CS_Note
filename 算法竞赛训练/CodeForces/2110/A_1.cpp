#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=1e5+10;
int arr[N],n;
void fun()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    sort(arr+1,arr+1+n);
    int l=1,r=1;
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
        {
            if((arr[i]+arr[j])%2==0)
            {
                if(r+i<j+l)
                {
                    l=i;
                    r=j;
                }
            }
        }
    }
    printf("%d\n",n-r+l-1);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}