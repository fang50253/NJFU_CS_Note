#include<bits/stdc++.h>
using namespace std;
const int N=30;
int main()
{
    int n;
    scanf("%d",&n);
    queue<int>que1,que2;
    unordered_set<int>s;
    for(int i=1;i<=2*n;++i)
    {
        int x;
        scanf("%d",&x);
        if(s.count(x)) que2.push(x);
        else que1.push(x);
        s.insert(x);
    }
    while(que1.size())
    {
        printf("%d ",que1.front());
        que1.pop();
    }
    printf("\n");
    while(que2.size())
    {
        printf("%d ",que2.front());
        que2.pop();
    }
    return 0;
}