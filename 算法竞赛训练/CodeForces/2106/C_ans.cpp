#include <cstdio>
#include <algorithm>
using namespace std;
const int N=2e5+11;
int a[N], b[N];
int main() 
{
	int t;
	scanf("%d", &t);
	while(t--) 
    {
		int n, k;
		scanf("%d%d", &n, &k);
		for(int i=1; i<=n; i++) scanf("%d", &a[i]);
		for(int i=1; i<=n; i++) scanf("%d", &b[i]);
		bool flag = 0;
		for(int i=1; i<=n && !flag; i++) 
			if(b[i]!=-1) flag=1;
		if(!flag) 
        {
			int mx = 0x3f3f3f3f, maxx = -1;
			for(int i=1; i<=n; i++) mx=min(mx, a[i]), maxx=max(maxx, a[i]);
			printf("%d\n", k - (maxx - mx) + 1);
		} 
        else 
        {
			bool isZero = 0;
			int lastSum = -1;
			for(int i=1; i<=n; i++) 
            {
				if(b[i] == -1) continue;
				if(lastSum != -1) 
                {
					if(lastSum != a[i] + b[i]) 
                    {
						isZero = 1;
						break;
					}
				}
				lastSum = a[i] + b[i];
			}
			for(int i=1;i<=n;i++) 
            {
				if(b[i]!=-1) lastSum=a[i]+b[i];
				if(lastSum == -1) continue;
				if(lastSum<b[i]||lastSum<a[i]||k +a[i]<lastSum) 
                {
					isZero = 1;
					break;
				}
			}
			if(isZero) printf("0\n");
			else printf("1\n");
		}
	}
	return 0;
}