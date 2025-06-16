#include<stdio.h>
#include<string>
#include<string.h>
#include<iostream>
using namespace std;
string str[8]={"N","NE","E","SE","S","SW","W","NW"};
int main()
{
    string input;
    cin>>input;
    for(int i=0;i<8;++i)
    {
        if(input==str[i])
        {
            cout<<str[(i+4)%8];
            return 0;
        }
    }
    return 0;
}