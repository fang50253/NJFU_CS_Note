#include<bits/stdc++.h>
using namespace std;
void fun()
{
    int n,x,y,cnt4=0,cnt8=0;
    scanf("%d%d%d",&n,&x,&y);
    if(x<0) x=-x;
    if(y<0) y=-y;
    if(x<y) swap(x,y);
    string str;
    cin>>str;
    for(int i=0;i<str.length();++i)
    {
        if(str[i]=='4') ++cnt4;
        else ++cnt8;
    }
    if(x>cnt4+cnt8) printf("NO\n");
    else if(x<=cnt8) printf("YES\n");
    else if(y<=cnt8)  printf("YES\n");
    else if(x+y<=cnt8*2+cnt4) printf("YES\n");
    else printf("NO\n");

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