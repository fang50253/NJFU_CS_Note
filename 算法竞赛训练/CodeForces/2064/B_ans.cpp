#include<cstdio>
int a[200001],c[200001];
int main()
{
	int t,n,i,l,m,p;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n),l=m=0;
		for(i=1;i<=n;i++)c[i]=0;
		for(i=1;i<=n;i++)
			scanf("%d",a+i),c[a[i]]++;
		for(i=1;i<=n;i++)
			if(c[a[i]]>1)l=i;
			else
				if(i-l>m)m=i-l,p=i;
		if(m)printf("%d %d\n",p-m+1,p);
		else puts("0");
	}
}
