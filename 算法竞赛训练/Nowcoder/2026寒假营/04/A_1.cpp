#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10;
int arr[N];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d",&arr[i]);
    }
    sort(arr+1,arr+1+n);
    int cnt=0,ans=0;
    int mid=arr[int(ceil(0.8*(n-1)))+1];
    for(int i=1;i<=n;++i){
        if(arr[i]>=mid){
            ans+=arr[i];
        }
    }
    printf("%d\n",ans);
    return 0;
}