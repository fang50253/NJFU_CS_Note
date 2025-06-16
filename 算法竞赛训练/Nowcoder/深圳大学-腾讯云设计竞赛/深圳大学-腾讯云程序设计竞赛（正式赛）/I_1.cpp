#include<stdio.h>
#include<string>
#include<algorithm>
#include<iostream>
using std::sort;
using std::string;
using std::cin;
using std::cout;
struct Node
{
    int hh,mm;
    string str;
    bool operator < (const Node &W) const
    {
        if(hh!=W.hh) return hh<W.hh;
        if(mm!=W.mm) return mm<W.mm;
        return str<W.str;
    }
}node[1100];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        auto &x=node[i];
        scanf("%d:%d",&x.hh,&x.mm);
        cin>>x.str;
    }
    sort(node,node+n);
    for(int i=0;i<n;++i)
    {
        auto &x=node[i];
        if(x.hh<10) printf("0%d:",x.hh);
        else printf("%d:",x.hh);
        if(x.mm<10) printf("0%d ",x.mm);
        else printf("%d ",x.mm);
        cout<<x.str;
        printf("\n");
    }
    return 0;
}