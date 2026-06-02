#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=0x3f3f3f3f3f3f3f3f;
void fun(){
    priority_queue<ll>que;
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        ll a;
        scanf("%lld",&a);
        que.push(a);
    }
    while(que.size()){
        //连着吐5个
        ll out[5];
        for(int i=0;i<5;++i){
            if(que.size()){
                out[i]=que.top();
                que.pop();
            }
            else{
                printf("F\n");
                return;
            }
        }
        for(int i=0;i<5;++i){
            if(out[i]==1) continue;
            else{
                que.push(out[i]-1);
            }
        }
    }
    printf("T\n");
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}