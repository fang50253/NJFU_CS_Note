#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct Node{
    int id,num;
}arr[N];
bool rk_id(Node a,Node b){
    return a.id<b.id;
}
bool rk_num(Node a,Node b){
    return a.num<b.num;
}
void fun(){
    unordered_map<int,int>mp;
    unordered_map<int,int>ans;
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d",&arr[i].num);
        arr[i].id=i;
        ++mp[arr[i].num];
    }
    sort(arr+1,arr+1+n,rk_num);
    bool flag=mp[arr[n].num]%2;//0表示最大数字出现偶数次，1表示奇数次
    if(flag==1){//奇数次
        ans[arr[n].num]=1;
        for(int i=1;i<=n;++i){
            if(ans.count(arr[i].num)) continue;
            else ans[arr[i].num]=0;
        }
    }
    else{
        ans[arr[n].num]=0;
        for(int i=1;i<=n;++i){
            if(ans.count(arr[i].num)) continue;
            else ans[arr[i].num]=1;
        }
    }
    sort(arr+1,arr+1+n,rk_id);
    for(int i=1;i<=n;++i){
        printf("%d",ans[arr[i].num]);
    }
    printf("\n");
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}