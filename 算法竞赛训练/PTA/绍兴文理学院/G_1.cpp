#include<bits/stdc++.h>
using namespace std;
string str;
int main()
{
    getline(cin,str);
    char ch='A';
    for(int i=0;i<str.size();i++){
        if(str[i]==' '){
            str[i]=ch++;
            if(ch>'Z') ch='A';
        }
    }
    cout<<str<<endl;
    return 0;
}