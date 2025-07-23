#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<cmath>
#include<utility>
#include<unordered_map>
#include<queue>
#include<stack>
#include<cstdlib>
#include<string.h>
#include<stdlib.h>
#include<unordered_set>
#define PII pair<int,int>
using namespace std;
typedef long long ll;
ll cnt[30];
void fun()
{
    string str,res;
    cin>>str;
    memset(cnt,0,sizeof cnt);
    for (char c:str) ++cnt[c -'A'];
    while (cnt['F'-'A']>=2&&cnt['T'-'A']>=1)
    {
        res += "FTF";
        cnt['F' - 'A'] -= 2;
        cnt['T' - 'A'] -= 1;
    }
    while (cnt['N'-'A']>=1&&cnt['T'-'A']>=2)
    {
        res+="TNT";
        cnt['N'-'A']-=1;
        cnt['T'-'A']-=2;
    }
    for (int i=0;i<26;++i) res+=string(cnt[i],'A'+i);
    cout<<res<<endl;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}