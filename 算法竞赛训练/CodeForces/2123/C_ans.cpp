#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2e5 + 10;
int arr[N], leftMin[N], rightMax[N];

void fun() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }

    // 构建左侧最小值数组
    leftMin[1] = arr[1];
    for (int i = 2; i <= n; ++i)
        leftMin[i] = min(leftMin[i - 1], arr[i]);

    // 构建右侧最大值数组
    rightMax[n] = arr[n];
    for (int i = n - 1; i >= 1; --i)
        rightMax[i] = max(rightMax[i + 1], arr[i]);

    // 判断每个位置是否满足两侧单调条件
    for (int i = 1; i <= n; ++i) {
        if (arr[i] >= leftMin[i] && arr[i] <= rightMax[i])
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) fun();
    return 0;
}