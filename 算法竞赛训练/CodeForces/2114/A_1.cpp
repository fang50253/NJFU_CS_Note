#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
const int N=2e5+10;
int num(string str,int l,int r)
{
    int ans=0;
    for(int i=l;i<=r;++i)
    {
        ans=ans*10+str[i]-'0';
    }
    return ans;
}
void fun()
{
    string str;
    cin>>str;
    for(int i=1;i<=str.length();++i)
    {
        int a=num(str,0,i-1);;
        int b=num(str,i,str.size()-1);
        if((a+b)*(a+b)==num(str,0,str.size()-1))
        {
            printf("%d %d\n",a,b);
            return;
        }
    }
    printf("-1\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}