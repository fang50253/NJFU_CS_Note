#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[500005];
void solve(){
	int n,ans=0;cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		if(i==n||a[i]>a[i+1])ans+=i*(n-i+1);
		else ans+=i;
	}
	cout<<ans<<'\n';
}
signed main(){
	int T;cin>>T;
	while(T--)solve();
}