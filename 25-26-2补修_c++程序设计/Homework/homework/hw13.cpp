//assignment
// 定义 NewString 公有继承自 ReString、CopyString、CmpString
// 1.在程序中体现多重继承中构造函数调用顺序
// 2.用三种不同的手段解决二义性问题
// 3.为基类 BaseString、ReString、CopyString、CmpString 带参数的构造函数，实现构造函数参数的参数传递
// 其他要求：
// 1.主函数实现对以上所有类中定义的功能的验证
// 2.类中定义的成员函数的函数体在类外完成
// 3.在结构设计中作出类继承关系图

#include<iostream>
#include<cstring>
using std::cout;
using std::cin;
using std::endl;

// 基类 BaseString
class BaseString {
protected:
    char Data[50];
    unsigned int Length;

public:
    BaseString();
    BaseString(const char* str);
    BaseString(const BaseString& ob);
    ~BaseString();
    
    unsigned int GetLength();
    void Display();
    char* GetData();
    void Input();
};

// BaseString 类外实现
BaseString::BaseString() {
    Data[0] = '\0';
    Length = 1;
    cout << "BaseString 构造函数被调用" << endl;
}

BaseString::BaseString(const char* str) {
    strcpy(Data, str);
    Length = strlen(str) + 1;
    cout << "BaseString 带参数构造函数被调用, 参数: " << str << endl;
}

BaseString::BaseString(const BaseString& ob) {
    strcpy(Data, ob.Data);
    Length = ob.Length;
    cout << "BaseString 拷贝构造函数被调用" << endl;
}

BaseString::~BaseString() {
    cout << "BaseString 析构函数被调用" << endl;
}

unsigned int BaseString::GetLength() {
    return Length;
}

void BaseString::Display() {
    cout << "字符串内容: " << Data << endl;
    cout << "字符串长度: " << Length << " (包括结束符)" << endl;
    cout << "实际字符数: " << Length - 1 << endl;
}

char* BaseString::GetData() {
    return Data;
}

void BaseString::Input() {
    cout << "请输入字符串 (最多49个字符): ";
    cin.getline(Data, 50);
    Length = strlen(Data) + 1;
}

// 公有派生类 ReString
class ReString : virtual public BaseString {
public:
    ReString();
    ReString(const char* str);
    ReString(const ReString& ob);
    ~ReString();
    void Inverse();
    void Display();
};

ReString::ReString() : BaseString() {
    cout << "ReString 构造函数被调用" << endl;
}

ReString::ReString(const char* str) : BaseString(str) {
    cout << "ReString 带参数构造函数被调用, 参数: " << str << endl;
}

ReString::ReString(const ReString& ob) : BaseString(ob) {
    cout << "ReString 拷贝构造函数被调用" << endl;
}

ReString::~ReString() {
    cout << "ReString 析构函数被调用" << endl;
}

void ReString::Inverse() {
    int len = strlen(Data);
    for(int i = 0; i < len / 2; i++) {
        char temp = Data[i];
        Data[i] = Data[len - 1 - i];
        Data[len - 1 - i] = temp;
    }
    cout << "字符串已倒置" << endl;
}

void ReString::Display() {
    BaseString::Display();
}

// 保护派生类 CopyString
class CopyString : virtual public BaseString {
public:
    CopyString();
    CopyString(const char* str);
    CopyString(const CopyString& ob);
    ~CopyString();
    void Copy(const CopyString &ob);
    void Copy(const char* str);
    void Display();
    void Input();
    char* GetData();
};

CopyString::CopyString() : BaseString() {
    cout << "CopyString 构造函数被调用" << endl;
}

CopyString::CopyString(const char* str) : BaseString(str) {
    cout << "CopyString 带参数构造函数被调用, 参数: " << str << endl;
}

CopyString::CopyString(const CopyString& ob) : BaseString(ob) {
    cout << "CopyString 拷贝构造函数被调用" << endl;
}

CopyString::~CopyString() {
    cout << "CopyString 析构函数被调用" << endl;
}

void CopyString::Copy(const CopyString &ob) {
    strcpy(Data, ob.Data);
    Length = ob.Length;
    cout << "字符串拷贝完成 (从CopyString对象)" << endl;
}

void CopyString::Copy(const char* str) {
    strcpy(Data, str);
    Length = strlen(str) + 1;
    cout << "字符串拷贝完成 (从C字符串)" << endl;
}

void CopyString::Display() {
    BaseString::Display();
}

void CopyString::Input() {
    BaseString::Input();
}

char* CopyString::GetData() {
    return BaseString::GetData();
}

// 私有派生类 CmpString
class CmpString : virtual public BaseString {
public:
    CmpString();
    CmpString(const char* str);
    CmpString(const CmpString& ob);
    ~CmpString();
    int Compare(const CmpString &ob);
    void Display();
    void Input();
    char* GetData();
    unsigned int GetLength();
};

CmpString::CmpString() : BaseString() {
    cout << "CmpString 构造函数被调用" << endl;
}

CmpString::CmpString(const char* str) : BaseString(str) {
    cout << "CmpString 带参数构造函数被调用, 参数: " << str << endl;
}

CmpString::CmpString(const CmpString& ob) : BaseString(ob) {
    cout << "CmpString 拷贝构造函数被调用" << endl;
}

CmpString::~CmpString() {
    cout << "CmpString 析构函数被调用" << endl;
}

int CmpString::Compare(const CmpString &ob) {
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

void CmpString::Display() {
    BaseString::Display();
}

void CmpString::Input() {
    BaseString::Input();
}

char* CmpString::GetData() {
    return BaseString::GetData();
}

unsigned int CmpString::GetLength() {
    return BaseString::GetLength();
}

// 多重继承类 NewString
class NewString : public ReString, public CopyString, public CmpString {
public:
    NewString();
    NewString(const char* str);
    ~NewString();
    
    // 解决二义性问题的手段1：使用作用域分辨符
    void Display1();
    
    // 解决二义性问题的手段2：重新定义函数
    void Display2();
    
    // 解决二义性问题的手段3：使用using声明
    using ReString::Display;
    
    // 解决GetData的二义性：在NewString中重新定义
    char* GetData();
    
    // 展示各基类功能
    void ShowAllFeatures();
};

// NewString 类外实现
NewString::NewString() 
    : BaseString(), ReString(), CopyString(), CmpString() {
    cout << "NewString 构造函数被调用" << endl;
}

NewString::NewString(const char* str) 
    : BaseString(str), ReString(str), CopyString(str), CmpString(str) {
    cout << "NewString 带参数构造函数被调用, 参数: " << str << endl;
}

NewString::~NewString() {
    cout << "NewString 析构函数被调用" << endl;
}

// 解决GetData的二义性：明确使用BaseString的GetData
char* NewString::GetData() {
    return BaseString::GetData();
}

// 手段1：使用作用域分辨符明确调用哪个基类的函数
void NewString::Display1() {
    cout << "\n使用作用域分辨符解决二义性:" << endl;
    cout << "调用 ReString::Display(): " << endl;
    ReString::Display();
    cout << "调用 CopyString::Display(): " << endl;
    CopyString::Display();
    cout << "调用 CmpString::Display(): " << endl;
    CmpString::Display();
}

// 手段2：重新定义函数，在内部选择调用
void NewString::Display2() {
    cout << "\n重新定义函数解决二义性:" << endl;
    cout << "选择使用 ReString 的显示功能: " << endl;
    ReString::Display();
}

// 展示所有功能
void NewString::ShowAllFeatures() {
    cout << "\nNewString 综合功能展示:" << endl;
    
    // 使用 ReString 的倒置功能
    cout << "\nReString 功能 (倒置):" << endl;
    cout << "倒置前: ";
    ReString::Display();
    Inverse();
    cout << "倒置后: ";
    ReString::Display();
    
    // 使用 CopyString 的拷贝功能 (使用作用域分辨符解决二义性)
    cout << "\nCopyString 功能 (拷贝):" << endl;
    CopyString cs("Target String");
    cout << "源对象: ";
    cs.Display();
    // 明确使用 CopyString 的 Copy 函数
    CopyString::Copy(cs);
    cout << "拷贝后当前对象: ";
    CopyString::Display();
    
    // 使用 CmpString 的比较功能
    cout << "\nCmpString 功能 (比较):" << endl;
    CmpString cmp1("ABC");
    CmpString cmp2("ABCDEF");
    cout << "cmp1: ";
    cmp1.Display();
    cout << "cmp2: ";
    cmp2.Display();
    int result = CmpString::Compare(cmp2);
    if(result == 1) {
        cout << "当前对象长度 > cmp2长度" << endl;
    }
    else if(result == 0) {
        cout << "当前对象长度 = cmp2长度" << endl;
    }
    else {
        cout << "当前对象长度 < cmp2长度" << endl;
    }
    
    // 演示 GetData 的使用
    cout << "\nGetData 功能演示:" << endl;
    char* dataPtr = GetData();
    cout << "通过 GetData() 获取的字符串: " << dataPtr << endl;
}

int main() {
    cout << "测试多重继承构造函数调用顺序:" << endl;
    
    // 测试构造函数调用顺序
    cout << "\n创建 NewString 对象 (无参构造):" << endl;
    NewString ns1;
    
    cout << "\n创建 NewString 对象 (带参构造):" << endl;
    NewString ns2("MultiInheritance");
    
    cout << "\n测试三种解决二义性的方法:" << endl;
    
    NewString ns3("Hello World");
    
    // 手段1：作用域分辨符
    ns3.Display1();
    
    // 手段2：重新定义函数
    ns3.Display2();
    
    // 手段3：using声明（已在类中声明，直接调用）
    cout << "\n使用 using 声明解决二义性:" << endl;
    ns3.Display();
    
    cout << "\n测试所有类功能:" << endl;
    
    // 测试 BaseString
    cout << "\nBaseString 功能测试:" << endl;
    BaseString base;
    base.Input();
    base.Display();
    
    // 测试 ReString
    cout << "\nReString 功能测试:" << endl;
    ReString re("ABC");
    cout << "倒置前: ";
    re.Display();
    re.Inverse();
    cout << "倒置后: ";
    re.Display();
    
    // 测试 CopyString
    cout << "\nCopyString 功能测试:" << endl;
    CopyString copy1("Source");
    CopyString copy2;
    cout << "copy1: ";
    copy1.Display();
    copy2.Copy(copy1);
    cout << "copy2拷贝后: ";
    copy2.Display();
    
    // 测试 CmpString
    cout << "\nCmpString 功能测试:" << endl;
    CmpString cmpA("Short");
    CmpString cmpB("LongerString");
    cout << "cmpA: ";
    cmpA.Display();
    cout << "cmpB: ";
    cmpB.Display();
    int cmpResult = cmpA.Compare(cmpB);
    if(cmpResult == 1) {
        cout << "cmpA长度 > cmpB长度" << endl;
    }
    else if(cmpResult == 0) {
        cout << "cmpA长度 = cmpB长度" << endl;
    }
    else {
        cout << "cmpA长度 < cmpB长度" << endl;
    }
    
    // 测试 NewString 综合功能
    cout << "\nNewString 综合功能测试:" << endl;
    NewString ns4("TestString");
    ns4.ShowAllFeatures();
    
    cout << "\n对象销毁，观察析构顺序:" << endl;
    
    return 0;
}