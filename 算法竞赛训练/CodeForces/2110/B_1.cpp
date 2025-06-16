#include<stdio.h>
#include<string>
#include<iostream>
#include<stack>
using namespace std;
const int N=2e5+10;
void fun()
{
    string str;
    cin>>str;
    stack<char>st;
    if(str[0]==')')
    {
        printf("No\n");
        return;
    }
    else st.push('(');
    for(size_t i=1;i<str.length();++i)
    {
        if(str[i]==')')
        {
            st.pop();
            if(st.empty())
            {
                if(i==str.length()-1)
                {
                    printf("No\n");
                    return;
                }
                else
                {
                    printf("Yes\n");
                    return;
                }
            }
        }
        else st.push('(');
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}