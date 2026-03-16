#include<bits/stdc++.h>
using namespace std;
int main(){
    unordered_set<int>st;
    for(int i=1;i<=100;++i){
        st.insert(i*(i+1));
    }
    int x;
    scanf("%d",&x);
    if(st.count(x)){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
    return 0;
}