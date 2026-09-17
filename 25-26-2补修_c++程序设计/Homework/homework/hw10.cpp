// assignment
// 定义 BaseString 的公有派生类 ReString，实现字符串的倒置功能
// void Inverse() // 如原字符串"ABC"，倒置后"CBA"

#include<iostream>
#include<cstring>
using std::cout;
using std::cin;
using std::endl;

class BaseString {
protected:
    char Data[50];          // 字符串数组
    unsigned int Length;    // 字符串长度，包括结束字符'\0'

public:
    // 构造函数
    BaseString() {
        Data[0] = '\0';
        Length = 1;
    }
    
    // 带参数构造函数
    BaseString(const char* str) {
        strcpy(Data, str);
        Length = strlen(str) + 1;
    }
    
    // 析构函数
    ~BaseString() {
    }
    
    // 返回字符串长度成员函数
    unsigned int GetLength() {
        return Length;
    }
    
    // 输出数据成员函数
    void Display() {
        cout << "字符串内容: " << Data << endl;
        cout << "字符串长度: " << Length << " (包括结束符)" << endl;
        cout << "实际字符数: " << Length - 1 << endl;
    }
    
    // 类外访问数据成员函数
    char* GetData() {
        return Data;
    }
    
    // 成员函数实现键盘输入字符串
    void Input() {
        cout << "请输入字符串 (最多49个字符): ";
        cin.getline(Data, 50);
        Length = strlen(Data) + 1;
    }
};

// 公有派生类 ReString，实现字符串的倒置功能
class ReString : public BaseString {
public:
    // 构造函数
    ReString() : BaseString() {
    }
    
    // 带参数构造函数
    ReString(const char* str) : BaseString(str) {
    }
    
    // 析构函数
    ~ReString() {
    }
    
    // 字符串倒置功能
    void Inverse() {
        int len = strlen(Data);
        for(int i = 0; i < len / 2; i++) {
            char temp = Data[i];
            Data[i] = Data[len - 1 - i];
            Data[len - 1 - i] = temp;
        }
        cout << "字符串已倒置" << endl;
    }
};

int main() {
    cout << "测试 ReString 类" << endl;
    
    // 测试无参构造
    cout << "\n创建对象 str1 (无参构造)" << endl;
    ReString str1;
    str1.Input();
    cout << "\n倒置前: ";
    str1.Display();
    str1.Inverse();
    cout << "\n倒置后: ";
    str1.Display();
    
    // 测试带参构造
    cout << "\n创建对象 str2 (带参构造)" << endl;
    ReString str2("ABC");
    cout << "\n倒置前: ";
    str2.Display();
    str2.Inverse();
    cout << "\n倒置后: ";
    str2.Display();
    
    // 测试其他字符串
    cout << "\n创建对象 str3 (带参构造)" << endl;
    ReString str3("Hello World");
    cout << "\n倒置前: ";
    str3.Display();
    str3.Inverse();
    cout << "\n倒置后: ";
    str3.Display();
    
    cout << "\n对象即将销毁，观察析构顺序" << endl;
    
    return 0;
}