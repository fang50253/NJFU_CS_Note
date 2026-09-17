//assignment
// 定义 BaseString 的保护派生类 CopyString，实现字符串的 copy 功能
// void Copy(const CopyString &ob);把对象 ob 拷贝到当前对象成员中

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

// 保护派生类 CopyString，实现字符串的copy功能
class CopyString : protected BaseString {
public:
    // 构造函数
    CopyString() : BaseString() {
    }
    
    // 带参数构造函数
    CopyString(const char* str) : BaseString(str) {
    }
    
    // 拷贝构造函数
    CopyString(const CopyString& ob) : BaseString(ob) {
    }
    
    // 析构函数
    ~CopyString() {
    }
    
    // 把对象ob拷贝到当前对象成员中
    void Copy(const CopyString &ob) {
        strcpy(Data, ob.Data);
        Length = ob.Length;
        cout << "字符串拷贝完成" << endl;
    }
    
    // 重新定义Display函数（因为保护继承后基类公有成员在派生类中变为保护成员）
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
};

int main() {
    cout << "测试 CopyString 类" << endl;
    
    // 测试无参构造
    cout << "\n创建对象 str1 (无参构造)" << endl;
    CopyString str1;
    str1.Input();
    cout << "\nstr1的内容:" << endl;
    str1.Display();
    
    // 测试带参构造
    cout << "\n创建对象 str2 (带参构造)" << endl;
    CopyString str2("Hello World");
    cout << "\nstr2的内容:" << endl;
    str2.Display();
    
    // 测试Copy功能
    cout << "\n将str2拷贝到str1" << endl;
    str1.Copy(str2);
    cout << "\n拷贝后str1的内容:" << endl;
    str1.Display();
    
    // 测试拷贝构造函数
    cout << "\n创建对象 str3 (拷贝构造)" << endl;
    CopyString str3(str2);
    cout << "\nstr3的内容:" << endl;
    str3.Display();
    
    // 测试修改不影响原对象
    cout << "\n修改str3的内容" << endl;
    str3.Input();
    cout << "\n修改后str3的内容:" << endl;
    str3.Display();
    cout << "\nstr2的内容未受影响:" << endl;
    str2.Display();
    
    cout << "\n对象即将销毁，观察析构顺序" << endl;
    
    return 0;
}