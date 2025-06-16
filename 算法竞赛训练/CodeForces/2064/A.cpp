#include<stdio.h>
#include<string>
#include<iostream>
using std::string;
using std::cin;
void fun()
{
    int len;
    scanf("%d",&len);
    string st,str="";
    cin>>st;
    for(int i=0;i<st.length();++i)
        if(i==0||st[i-1]!=st[i]) 
            str+=st[i];
    if(str[0]=='0') printf("%d\n",str.length()-1);
    else printf("%d\n",str.length());
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}