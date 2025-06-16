#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
const int N=2e5+10;
void fun()
{
    cin>>str;
    int a=-1,b=-1;
    for(int i=1;i<str.length();i++)
    {
        if(str[i]=='A')
        {
            a=i;
            break;
        }
    }
    for(int i=a+1;i<str.length();i++)
    {
        if(str[i]=='B')
        {
            b=i;
            break;
        }
    }
    if(a==-1&&b==-1)
    {
        printf("Alice\n");
        return;
    }
    else if(b==-1)
    {
        
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}