#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
void fun()
{
    int n,ans=0;
    scanf("%d",&n);
    string str;
    cin>>str;
    if(str[str.length()-1]=='0') reverse(str.begin(), str.end());
    //cout<<str<<endl;
    str="0"+str;
    for(int i=0;i<n+1;++i)
    {
        if(i==0) ;
        else if(str[i]!=str[i-1]) ans+=2;
        else ++ans;
    }
    int i;
    for(i=0;i<n+1;++i)//判断是否全0
    {
        if(str[i]=='1') break;
    }
    if(i!=n+1)
    {
        int cnt0=0;
        if(str[1]=='0') ++cnt0;
        if(str[n]=='0') ++cnt0;
        if(cnt0==0) ans-=2;
        else if(cnt0==1) ans--;

    }

    printf("%d\n",ans);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}