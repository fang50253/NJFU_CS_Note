#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
int max(int a,int b)
{
    return a>b?a:b;
}
int min(int a,int b)
{
    return a>b?b:a;
}
void fun()
{
    int n;
    string str;
    cin>>n>>str;
    int maxpos=0,minpos=INF;
    for(size_t i=0;i<str.length();++i)
    {
        maxpos=max(maxpos,str[i]);
        minpos=min(minpos,str[i]);
    }
    printf("%d\n",maxpos);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}