#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;
void fun()
{
    int n;
    scanf("%d",&n);
    string str;
    int ans=0;
    cin>>str;
    for(int i=0;i<str.length();++i)
    {
        if(str[i]=='1') ans+=str.length()-1;
        else ans+=1;
    }
    printf("%d\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}