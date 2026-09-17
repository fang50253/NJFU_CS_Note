// assignment：
// 定义一个基类 BaseString，实现字符串基本的输入功能，其结构如下：
// 1.保护数据成员：
//   char Data[50]； // 字符串数组
//   unsigned int Length; // 字符串长度，包括结束字符'\0'
// 2.构造函数和析构函数实现继承关系中调用顺序
// 3.返回字符串长度成员函数 unsigned int GetLength();
// 4.输出数据成员函数 void Display()；
// 5.类外访问数据成员函数 char *GetData()；
// 6.成员函数实现键盘输入字符串，为类对象的数据成员赋值 void Input()；

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
        Length = 1;  // 只有结束字符，长度为1
        cout << "BaseString 构造函数被调用" << endl;
    }
    
    // 带参数构造函数
    BaseString(const char* str) {
        strcpy(Data, str);
        Length = strlen(str) + 1;  // +1 包括结束字符'\0'
        cout << "BaseString 带参数构造函数被调用" << endl;
    }
    
    // 析构函数
    ~BaseString() {
        cout << "BaseString 析构函数被调用" << endl;
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
        Length = strlen(Data) + 1;  // 更新长度，包括结束字符'\0'
    }
};

// 派生类示例，展示构造和析构的调用顺序
class DerivedString : public BaseString {
private:
    char ExtraData[20];
    
public:
    // 派生类构造函数
    DerivedString() : BaseString() {
        ExtraData[0] = '\0';
        cout << "DerivedString 构造函数被调用" << endl;
    }
    
    // 派生类带参数构造函数
    DerivedString(const char* str1, const char* str2) : BaseString(str1) {
        strcpy(ExtraData, str2);
        cout << "DerivedString 带参数构造函数被调用" << endl;
    }
    
    // 派生类析构函数
    ~DerivedString() {
        cout << "DerivedString 析构函数被调用" << endl;
    }
    
    // 派生类自己的Display函数
    void Display() {
        BaseString::Display();
        cout << "额外数据: " << ExtraData << endl;
    }
};

int main() {
    cout << "测试基类 BaseString" << endl;
    
    // 测试无参构造函数
    cout << "\n创建对象 obj1 (无参构造)" << endl;
    BaseString obj1;
    obj1.Display();
    
    // 测试Input函数
    cout << "\n调用 Input() 函数" << endl;
    obj1.Input();
    obj1.Display();
    
    // 测试GetData函数
    cout << "\n调用 GetData() 函数" << endl;
    char* p = obj1.GetData();
    cout << "通过GetData获取的字符串: " << p << endl;
    
    // 测试带参数构造函数
    cout << "\n创建对象 obj2 (带参构造)" << endl;
    BaseString obj2("Hello World");
    obj2.Display();
    
    // 测试GetLength函数
    cout << "\n测试 GetLength()" << endl;
    cout << "obj2的字符串长度: " << obj2.GetLength() << endl;
    
    cout << "\n测试继承关系中的构造和析构调用顺序" << endl;
    
    // 测试派生类无参构造
    cout << "\n创建派生类对象 derived1 (无参构造)" << endl;
    DerivedString derived1;
    derived1.Display();
    
    // 测试派生类带参构造
    cout << "\n创建派生类对象 derived2 (带参构造)" << endl;
    DerivedString derived2("Base String", "Extra Info");
    derived2.Display();
    
    cout << "\n对象即将销毁，观察析构顺序" << endl;
    
    return 0;
}