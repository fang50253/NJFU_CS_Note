#include<stdio.h>
#include<string.h>
#include<queue>
#include<stack>
#include<set>
#include<string>
#include<iostream>
using namespace std;
typedef long long ll;
const ll N = 1e6 + 10;
ll n, m, T, num;
stack<ll> st;
multiset<ll> low, high; //不去重set 
string s;
 
void fun() {    //维护两个堆，并且low堆比high多一个元素 
    while (low.size() < high.size()) {
        low.insert(*high.begin());
        high.erase(high.begin());
    }
    while (low.size() > high.size() + 1) {
        auto it = low.end();
        it--;
        high.insert(*it);
        low.erase(it);
    }
}
 
int main() {
    cin >> T;
    while (T--) {
        cin >> s;
        if (s == "Pop") {
            if (st.empty())cout << "Invalid" << endl;
            else {
                cout << st.top() << endl;
                ll x = st.top();
                st.pop();
                if (low.find(x) != low.end())low.erase(low.find(x)); //寻找元素在哪个堆并删除
                else if (high.find(x) != high.end())high.erase(high.find(x));
                fun();//删除元素后维护一下两个堆的合法性	
            }
        } else if (s == "Push") {
            cin >> num;
            st.push(num);
            if (high.empty() || num < *high.begin())low.insert(num);    //判断元素应该进入哪个堆
            else high.insert(num);
            fun();
        } else if (s == "PeekMedian") {
            if (st.empty())cout << "Invalid" << endl;
            else {
                auto it = low.end();
                it--;
                cout << *it << endl;    //指针输出low堆最大的元素就是中值 
            }
        }
    }
} 