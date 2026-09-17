// assignment
// 定义 BaseString 的私有派生类 CmpString，实现字符串的比较功能
// 1.int Compare(const CmpString &ob);
// 2.返回值 = 1，表示当前对象字符串长度 > ob 字符串长度
// 3.返回值 = 0，表示当前对象字符串长度 = ob 字符串长度
// 4.返回值 = -1，表示当前对象字符串长度 < ob 字符串长度

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
    
    // 拷贝构造函数
    BaseString(const BaseString& ob) {
        strcpy(Data, ob.Data);
        Length = ob.Length;
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

// 私有派生类 CmpString，实现字符串的比较功能
class CmpString : private BaseString {
public:
    // 构造函数
    CmpString() : BaseString() {
    }
    
    // 带参数构造函数
    CmpString(const char* str) : BaseString(str) {
    }
    
    // 拷贝构造函数
    CmpString(const CmpString& ob) : BaseString(ob) {
    }
    
    // 析构函数
    ~CmpString() {
    }
    
    // 字符串比较函数
    int Compare(const CmpString &ob) {
        if(Length > ob.Length) {
            return 1;
        }
        else if(Length == ob.Length) {
            return 0;
        }
        else {
            return -1;
        }
    }
    
    // 重新定义Display函数（因为私有继承后基类公有成员在派生类中变为私有成员）
    void Display() {
        BaseString::Display();
    }
    
    // 重新定义Input函数
    void Input() {
        BaseString::Input();
    }
    
    // 重新定义GetData函数
    char* GetData() {
        return BaseString::GetData();
    }
    
    // 重新定义GetLength函数
    unsigned int GetLength() {
        return BaseString::GetLength();
    }
};

int main() {
    cout << "测试 CmpString 类" << endl;
    
    // 测试无参构造
    cout << "\n创建对象 str1 (无参构造)" << endl;
    CmpString str1;
    str1.Input();
    cout << "\nstr1的内容:" << endl;
    str1.Display();
    
    // 测试带参构造
    cout << "\n创建对象 str2 (带参构造)" << endl;
    CmpString str2("Hello");
    cout << "\nstr2的内容:" << endl;
    str2.Display();
    
    // 测试带参构造
    cout << "\n创建对象 str3 (带参构造)" << endl;
    CmpString str3("Hello World");
    cout << "\nstr3的内容:" << endl;
    str3.Display();
    
    // 测试比较功能
    cout << "\n比较 str2 和 str1" << endl;
    int result = str2.Compare(str1);
    if(result == 1) {
        cout << "str2字符串长度 > str1字符串长度" << endl;
    }
    else if(result == 0) {
        cout << "str2字符串长度 = str1字符串长度" << endl;
    }
    else {
        cout << "str2字符串长度 < str1字符串长度" << endl;
    }
    
    cout << "\n比较 str2 和 str3" << endl;
    result = str2.Compare(str3);
    if(result == 1) {
        cout << "str2字符串长度 > str3字符串长度" << endl;
    }
    else if(result == 0) {
        cout << "str2字符串长度 = str3字符串长度" << endl;
    }
    else {
        cout << "str2字符串长度 < str3字符串长度" << endl;
    }
    
    cout << "\n比较 str1 和 str1 (自身比较)" << endl;
    result = str1.Compare(str1);
    if(result == 1) {
        cout << "str1字符串长度 > str1字符串长度" << endl;
    }
    else if(result == 0) {
        cout << "str1字符串长度 = str1字符串长度" << endl;
    }
    else {
        cout << "str1字符串长度 < str1字符串长度" << endl;
    }
    
    // 显示各对象的实际长度
    cout << "\n各对象实际字符数:" << endl;
    cout << "str1: " << str1.GetLength() - 1 << " 个字符" << endl;
    cout << "str2: " << str2.GetLength() - 1 << " 个字符" << endl;
    cout << "str3: " << str3.GetLength() - 1 << " 个字符" << endl;
    
    cout << "\n对象即将销毁，观察析构顺序" << endl;
    
    return 0;
}