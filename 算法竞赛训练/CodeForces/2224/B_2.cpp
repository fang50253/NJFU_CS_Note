#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll a[N];
void fun(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        scanf("%lld",&a[i]);
    }
    sort(a,a+n);
    //先预处理成0 1 2 3 4......再多余的从小到大的顺序
    int anti=0;//期待遇到的数字
    for(int i=0;i<n;++i){
        if(a[i]==anti) {
            swap(a[i],a[anti]);
            ++anti;
        }
    }
    sort(a+anti,a+n);
    // for(int i=0;i<n;++i){
    //     printf("%lld ",a[i]);
    // }
    // cout<<endl;
    ll ans=0,mexnum=0,maxnum=0,l=0,r=n-1,mid=anti-1;
    for(int i=0;i<n;++i){
        //mexnum记录了前i-1个数字的最小的没有出现过的数字
        //maxnum记录了前i-1个数字中最大的一个数字
        ll tmpmexnum,tmpmaxnum;
        //1.先假设选择了最小的一个数字
        if(a[l]==mexnum) tmpmexnum=mexnum+1;
        else tmpmexnum=mexnum;
        if(a[l]>maxnum) tmpmaxnum=a[l];
        else tmpmaxnum=maxnum;
        ll t1=tmpmaxnum+tmpmexnum;
        //2.假设选择了最大的数字
        if(a[r]==mexnum) tmpmexnum=mexnum+1;
        else tmpmexnum=mexnum;
        if(a[r]>maxnum) tmpmaxnum=a[r];
        else tmpmaxnum=maxnum;
        ll t2=tmpmaxnum+tmpmexnum;
        // //3.假设选择了中间的数字
        // if(a[mid]==mexnum) tmpmexnum=mexnum+1;
        // else tmpmexnum=mexnum;
        // if(a[mid]>maxnum) tmpmaxnum=a[mid];
        // else tmpmaxnum=maxnum;
        // ll t3=tmpmaxnum+tmpmexnum;
        //如果选择最小的一个数字比较大
        // ll t=max(t1,max(t2,t3));
        ll t=max(t1,t2);
        if(t==t1){
            //选择加入最小的一个
            if(a[l]==mexnum) mexnum=mexnum+1;
            if(a[l]>maxnum) maxnum=a[l];
            ++l;
        }
        else if(t==t2){//&&r>=anti) {
            if(a[r]==mexnum) mexnum=mexnum+1;
            if(a[r]>maxnum) maxnum=a[r];
            --r;
        }
        // else {
        //     if(a[mid]==mexnum) mexnum=mexnum+1;
        //     if(a[mid]>maxnum) maxnum=a[r];
        //     --r;
        // }
        //cout<<maxnum<<" "<<mexnum<<endl;
        ans+=maxnum+mexnum;
    }
    printf("%lld\n",ans);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}