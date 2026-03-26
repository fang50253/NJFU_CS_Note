#include<iostream>
using namespace std;
int A[100010]={0},B[100010]={0},C[100010],D[100010];
int main()
{
    //首先读入两个数字a，b 
    string a,b;
    int sign=1;  // 1表示正，-1表示负
    cin>>a>>b;
    if(a[0]=='-'){
        sign*=-1;
        a=a.substr(1);  // 移除负号
    }
    if(a[0]=='+') {
        a=a.substr(1);  // 移除正号
    }
    // 处理第二个数的符号
    if(b[0]=='-') {
        sign*=-1;
        b=b.substr(1);  // 移除负号
    }
    if(b[0]=='+') {
        b=b.substr(1);  // 移除正号
    }
    //下面对数组进行逆序 
    for(int i=a.length()-1,j=1;i>=0;i--,j++) A[j]=a[i]-'0';
    for(int i=b.length()-1,j=1;i>=0;i--,j++) B[j]=b[i]-'0';
    //下面进行求积 
    for(int i=1;i<=a.length();i++)
    {
        for(int j=1;j<=b.length();j++)
        {
            C[i+j-1]+=A[i]*B[j];
        }
    }
    //下面处理进位
    int tmp=1;
    for(int i=1;i<=100005;i++)
    {
        C[tmp+1]+=C[tmp]/10;
        C[tmp]%=10;
        tmp++;
     } 
     //下面进行输出
    if(sign==-1) {
        cout << "-";
    }
     bool out=0;
     for(int i=100005;i>=1;i--)
     {
        if(C[i]) out=1;
        if(out) cout<<C[i];
      } 
      if(!out) cout<<0;
    return 0;
}