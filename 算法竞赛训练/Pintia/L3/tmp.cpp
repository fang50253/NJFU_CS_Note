#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1e4 + 10;
int n, m;
vector<int> coins, path, best_path;
bool dfs(int idx, int sum) 
{
    if (sum == m) 
    {
        best_path = path;
        return 1;
    }
    if (sum > m || idx >= n) return 0;
    for (int i = idx; i < n; i++) 
    {
        if (i > idx && coins[i] == coins[i - 1]) continue; // 避免重复选择相同值的硬币
        path.push_back(coins[i]);
        if (dfs(i + 1, sum + coins[i])) return 1; // 立即返回字典序最小解
        path.pop_back();
    }
    return 0;
}

int main() 
{
    cin >> n >> m;
    coins.resize(n);
    for (int i = 0; i < n; i++) cin >> coins[i];
    sort(coins.begin(), coins.end()); // 硬币升序排列，保证字典序最小
    if (dfs(0, 0)) 
    {
        for (int i = 0; i < best_path.size(); i++) 
        {
            if (i > 0) cout << " ";
            cout << best_path[i];
        }
        cout << endl;
    } 
    else cout << "No Solution" << endl;
    return 0;
}