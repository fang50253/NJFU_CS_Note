#include<stdio.h>
#include<queue>
#include<set>
#include<stack>
using namespace std;
multiset<int>small,big;
//确保每次答案都在big上，big的长度最多比small少1
stack<int>st;
void adjust()//调整对顶堆
{
    if(big.size()>small.size()+1)
    {
        small.insert(*big.begin());
        big.erase(big.begin());
    }
    if(big.size()<small.size())
    {
        auto x=small.end();
        --x;
        big.insert(*x);
        small.erase(x);
    }
}
int main()
{
    int T;
    char op[20];
    scanf("%d",&T);
    while(T--)
    {
        scanf(" %s",op);
        if(strcmp(op,"Pop")==0)
        {
            if(st.size()==0) printf("Invalid\n");
            else
            {
                printf("%d\n",st.top());
                auto x = st.top();
                st.pop();
                if (small.find(x) != small.end())small.erase(small.find(x)); //寻找元素在哪个堆并删除
                else if (big.find(x) != big.end())big.erase(big.find(x));
                adjust();//删除元素后维护一下两个堆的合法性	
            }
        }
        else if(strcmp(op,"Push")==0)
        {
            int x;
            scanf("%d",&x);
            st.push(x);
            if(x>=*big.begin()) big.insert(x);
            else small.insert(x);
            adjust();
        }
        else if(strcmp(op,"PeekMedian")==0)
        {
            if(st.size()==0) printf("Invalid\n");
            else if(big.size()==0) {auto it=small.end();--it;printf("%d\n",*it);}
            else printf("%d\n",*big.begin());
        }
    }
    return 0;
}