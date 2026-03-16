#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t[N],st[N];
int main(){
    int n,q,s;
    scanf("%d%d%d",&n,&q,&s);
    for(int i=1;i<=n;++i){
        scanf("%d",&t[i]);
    }
    st[1]=s;
    for(int i=2;i<=n;++i){
        st[i]=st[i-1]+t[i-1];
    }
    while(q--){
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",st[x]+y-1);
    }
    return 0;
}