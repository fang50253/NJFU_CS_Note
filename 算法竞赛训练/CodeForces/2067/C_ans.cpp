#include <iostream>
 
#define endl '\n'  // 定义 endl 为换行符，提高程序的可读性
 
using namespace std;
 
int t, n;  // t 为测试用例的数量，n 为每次测试的整数
 
// sol 函数用于根据给定的 n 来计算并返回结果
int sol(){
    string s;
    // 遍历 7 次，判断每次的条件
    for(int i=0; i<7; i++){
        s = to_string(n-i);  // 将 n-i 转换为字符串
        
        // 遍历字符串中的每一位字符
        for(int j=0; j<s.size(); j++)
            // 判断字符对应的数字是否满足条件
            if(('7'-s[j]+10)%10 <= i) 
                return i;  // 如果满足条件，返回 i
        
    }
 
    return 7;  // 如果没有找到满足条件的情况，返回 7
}
 
int main(){
    ios::sync_with_stdio(0);  // 加速输入输出
    cin.tie(0);  // 解除 cin 和 cout 的绑定，进一步提高效率
 
    cin >> t;  // 输入测试用例的数量
    while(t--){
        cin >> n;  // 输入每个测试用例中的整数 n
        
        cout << sol() << endl;  // 调用 sol 函数并输出结果
    }
 
    return 0;  // 程序结束
}