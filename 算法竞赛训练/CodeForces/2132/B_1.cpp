#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;
typedef long long ll;
void fun()
{
    string str,tmp;
    cin>>str;
    int ans=0;
    for(int i=2;i<=str.length();++i)
    {
        if(str.length()%i==0) ++ans;
    }
    printf("%d\n",ans);
    for(int i=2;i<=str.length();++i)
    {
        if(str.length()%i!=0) continue;
        tmp=str;
        for(int j=0;j<str.length();j+=2*i) 
            for(int k=j;k<j+i;++k)
                tmp[k]='0';
        bool flag=0;
        for(int j=0;j<str.length();++j)
        {
            if(tmp[j]!='0') flag=1;
            if(!flag) continue;
            cout<<tmp[j];
        }
        cout<<" ";
    }
    cout<<'\n';
}
int main()
{
    ios::sync_with_stdio();
    cin.tie(0);
    cout.tie(0);
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}