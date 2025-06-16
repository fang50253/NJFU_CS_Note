#include<stdio.h>
using namespace std;
typedef long long LL;
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
    {
		LL n,x;
		scanf("%lld%lld",&n,&x);
		int i=0,ans=0;
		for(;i<n;i++)
        {
			if((x|i)!=x) break;
			ans|=i;
			printf("%lld ",(i+1==n && ans!=x?x:i));
		}
		for(;i<n;i++) printf("%lld ",x);
		printf("\n");
	}
}