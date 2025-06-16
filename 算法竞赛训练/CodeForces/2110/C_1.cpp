#include<stdio.h>
#include<stack>
#include<math.h>
#include<algorithm>
using namespace std;
const int N=2e5+10;
int ori[N],l[N],h[N],n,dpl[N],dph[N],t[N];
void fun()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&ori[i]);
    for(int i=1;i<=n;++i) scanf("%d%d",&l[i],&h[i]);
    for(int i=1;i<=n;++i)
    {
        if(ori[i]==0)
        {
            dpl[i]=dpl[i-1];
            dph[i]=dph[i-1];
        }
        else if(ori[i]==1)
        {
            dpl[i]=dpl[i-1]+1;
            dph[i]=dph[i-1]=1;
        }
        else if(ori[i]==-1)
        {
            dpl[i]=dpl[i];
            dph[i]=dph[i]+1;
        }
        if(dph[i]<l[i]||dpl[i]>h[i])
        {
            printf("-1\n");
            return;
        }
        dph[i]=min(dph[i],h[i]);
        dpl[i]=max(dpl[i],l[i]);
    }
    stack<int>ans;
    int height=dpl[n];
    ans.push(height);
    for(int i=n-1;i>=1;--i)
    {
        if(ori[i]==0) ans.push(height);
        else if(ori[i]==1) ans.push(--height);
        else if(height>dpl[i]) ans.push(--height);
        else if(height>dpl[i]&&height<=dph[i]) ans.push(height);
        //else if(height<dpl[i]) ans.push(++height);
        
    }
    int index=1;
    while(ans.size())
    {
        t[index++]=ans.top();
        ans.pop();
    }
    for(int i=index-1;i>=1;--i) t[i]-=t[i-1];
    for(int i=1;i<=index-1;++i) printf("%d ",t[i]);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}