#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
const int N=2e5+10;
void fun()
{
    int n,k;
    cin>>n>>k;
    string str;
    cin>>str;
    for(int i=0,j=str.length()-1;i<j;++i,--j)
    {
        if(str[i]==str[j]&&str[i]=='1') --k;
    }
    if(k==0) printf("YES\n");
    else printf("NO\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}