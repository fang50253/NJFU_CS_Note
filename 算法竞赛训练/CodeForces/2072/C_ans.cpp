
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,x;
		cin>>n>>x;
		int i=0,ans=0;
		for(;i<n;i++){
			if((x|i)!=x) break;
			ans|=i;
			cout<<(i+1==n && ans!=x?x:i)<<" ";
		}
		for(;i<n;i++)cout<<x<<" ";
		cout<<endl;
	}
}