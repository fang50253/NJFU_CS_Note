#include<stdio.h>
#include<iostream>
using namespace std;
const int N=2e5+5;
int T,n,a[N];
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		long long num=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]<0)
			num-=a[i];
		}
		long long ans=num;
		for(int i=1;i<=n;i++){
			num+=a[i];
			ans=max(ans,num);
		}
		cout<<ans<<'\n';
	}
	return 0;
}