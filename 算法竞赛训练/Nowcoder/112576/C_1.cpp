#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
int arr[N],n;
void fun()
{
    scanf("%d",&n);
    int find;
    for(int i=1;i<=2*n;++i) scanf("%d",&arr[i]);
    for(int i=1;i<=2*n+1;++i)
    {
        if(i==1) find=arr[1];
        else if(arr[i]==find)
        {
            find=arr[++i];
            if(i==2*n+1)
            {
                printf("Yes\n");
                return;
            }
        }
    }
    printf("No\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}