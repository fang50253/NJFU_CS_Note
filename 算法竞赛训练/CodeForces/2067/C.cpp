#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<vector>
using namespace std;
int arr[20][20];//代表第i位上要加上j至少要x步
const int N=10;
void count() {
    // 初始化arr为最大值
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = INT_MAX; // 初始化为最大值
        }
    }

    // 对于每一位i
    for (int i = 0; i < N; i++) {
        // 对于每个j（0到9）
        for (int j = 0; j < N; j++) {
            // 如果j为0，不需要任何操作
            if (j == 0) {
                arr[i][j] = 0;
                continue;
            }

            // 尝试加不同的只由9组成的数
            long long num = 9; // 从9开始
            while (true) {
                // 计算加num后第i位的增量
                long long temp = num;
                int k = 0;
                while (temp > 0 && k < i) {
                    temp /= 10;
                    k++;
                }
                int increment = temp % 10; // 第i位的增量

                // 如果增量大于j，则停止
                if (increment > j) break;

                // 更新arr[i][j]
                if (increment == j) {
                    arr[i][j] = 1; // 只需要一步
                    break;
                } else if (increment < j) {
                    // 需要递归计算剩余的部分
                    int remaining = j - increment;
                    if (arr[i][remaining] != INT_MAX) {
                        arr[i][j] = min(arr[i][j], 1 + arr[i][remaining]);
                    }
                }

                // 下一个只由9组成的数
                num = num * 10 + 9;
            }
        }
    }
}

void print_table() {
    cout << "arr[i][j] 表格：" << endl;
    for (int i = 0; i < 10; i++) { // 仅打印 10 位，避免太大
        for (int j = 0; j < 10; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}
void fun()
{
    
}
int main()
{
    int T;
    count();
    print_table();
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}