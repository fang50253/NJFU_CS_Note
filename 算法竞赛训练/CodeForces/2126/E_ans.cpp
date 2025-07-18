#include<stdio.h>
#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;
const int N=2e5+5;
int t,n,m,a[N],b[N],f;
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
void fun()
{
    		cin>>n;
		f=1;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i];
		if(a[n]!=b[1])
		{
			printf("NO\n");
            return;
		}
		for(int i=1;i<n;i++){
			if(a[i]%a[i+1]!=0)
            {
                printf("NO\n");
                return;
            }
			if(b[i+1]%b[i]!=0)
            {
                printf("NO\n");
                return;
            }
		}
		for(int i=1;i<n;i++){
			if(gcd(a[i],b[i+1])!=a[n])
            {
                printf("NO\n");
                return;
            }
		}
		cout<<"YES\n";
}
int main(){
	cin>>t;
	while(t--) fun();
	return 0;
}