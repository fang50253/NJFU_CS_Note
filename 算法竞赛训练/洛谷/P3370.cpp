#include<stdio.h>
#include<unordered_map>
#include<string>
#include<iostream>
int main()
{
    int n;
    scanf("%d",&n);
    std::unordered_map<std::string,int>m;
    while(n--)
    {
        std::string s;
        std::cin>>s;
        m[s]++;
    }
    printf("%d\n",m.size());
    return 0;
}