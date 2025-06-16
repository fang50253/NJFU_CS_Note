#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
const int N=2e5+10;
void fun()
{
    int cnt1=0;
    string str;
    cin>>str;
    for(int i=0;i<str.length();++i)
        if(str[i]=='A') ++cnt1;
    int nodea=1,nodeb=1;
    while(cnt1!=0&&cnt1!=n)
    {
        while(str[nodea]!='A') ++nodea;
        nodeb=nodea+1;
        while(str[nodeb]!='B')
        {
            ++nodeb;
            if(nodeb==n) nodeb=0;
        }
        str[nodea]='B';
        ++nodeb;
        --nodea;
        if(nodeb==1)
        {
            str[nodea]='B';
            ++nodeb;
            --nodea;
        }
    }
    
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}