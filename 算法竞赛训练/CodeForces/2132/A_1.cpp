#include<stdio.h>
#include<deque>
#include<iostream>
using namespace std;
deque<char>dep;
void fun()
{
    int n1,n2;
    string str1,str2,str;
    cin>>n1>>str1>>n2>>str2>>str;
    //int l=0,r=n1-1;
    for(size_t i=0;i<str.length();++i)
    {
        if(str[i]=='V') str1.insert(str1.begin(),str2[i]);
        else str1=str1+str2[i];
    }
    cout<<str1<<'\n';
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