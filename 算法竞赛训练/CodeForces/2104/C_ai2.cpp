#include <bits/stdc++.h>
using namespace std;
bool beats(int b, int a, int n) 
{
    if (b == 1 && a == n) return 1;
    if (b == n && a == 1) return 0;
    return b > a;
}
int main() 
{
    int t;
    cin >> t;
    while (t--) 
    {
        int n;
        string s;
        cin >> n >> s;
        vector<int> A, B;
        A.reserve(n);
        B.reserve(n);
        for (int i = 0; i < n; i++) 
        {
            if (s[i] == 'A') A.push_back(i + 1);
            else B.push_back(i + 1);
        }
        bool flag = 1;
        for (int a : A) 
        {
            bool covered = 0;
            for (int b : B) 
            {
                if (beats(b, a, n)) 
                {
                    covered = 1;
                    break;
                }
            }
            if (!covered) 
            {
                flag = 0;
                break;
            }
        }
        cout << (flag ? "Bob\n" : "Alice\n");
    }
    return 0;
}