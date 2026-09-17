//assignment：
// 设计一个Date类，其结构如下：
// 1.私有数据成员 char* pYMD；//指向字符串的指针，表示“****年月日”
// 2.公有成员函数
// 3.重载构造函数实现数据成员初始化（带参数和Copy构造）
// 4.重载“=”运算符，实现对象直接赋值
// Date& Add([参数列表])；计算n天以后是“****年月日”
// Date& Sub([参数列表])；计算n天以前是“****年月日”
// void Display()；输出Date对象的数据“****年月日”

#include<iostream>
#include<cstring>
#include<cstdlib>
using std::cout;
using std::cin;
using std::endl;

class Date {
private:
    char* pYMD;  // 指向字符串的指针，表示“****年**月**日”

    // 辅助函数：判断是否为闰年
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    
    // 辅助函数：获取某月的天数
    int getDaysInMonth(int year, int month) const {
        int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(month == 2 && isLeapYear(year)) {
            return 29;
        }
        return days[month - 1];
    }
    
    // 辅助函数：从字符串解析年月日
    void parseDate(int& year, int& month, int& day) const {
        char str[20];
        strcpy(str, pYMD);
        
        char* token = strtok(str, "年月日");
        year = atoi(token);
        token = strtok(NULL, "年月日");
        month = atoi(token);
        token = strtok(NULL, "年月日");
        day = atoi(token);
    }
    
    // 辅助函数：格式化日期字符串
    void formatDate(int year, int month, int day) {
        delete[] pYMD;
        pYMD = new char[20];
        sprintf(pYMD, "%d年%02d月%02d日", year, month, day);
    }

public:
    // 默认构造函数
    Date() {
        pYMD = new char[20];
        strcpy(pYMD, "1970年01月01日");
    }
    
    // 带参数构造函数
    Date(const char* str) {
        pYMD = new char[20];
        strcpy(pYMD, str);
    }
    
    // 带年月日参数的构造函数
    Date(int year, int month, int day) {
        pYMD = new char[20];
        sprintf(pYMD, "%d年%02d月%02d日", year, month, day);
    }
    
    // 拷贝构造函数
    Date(const Date& ob) {
        pYMD = new char[20];
        strcpy(pYMD, ob.pYMD);
    }
    
    // 析构函数
    ~Date() {
        delete[] pYMD;
    }
    
    // 重载“=”运算符
    Date& operator=(const Date& ob) {
        if(this != &ob) {
            delete[] pYMD;
            pYMD = new char[20];
            strcpy(pYMD, ob.pYMD);
        }
        return *this;
    }
    
    // 计算n天以后的日期
    Date& Add(int n) {
        if(n < 0) {
            return Sub(-n);
        }
        
        int year, month, day;
        parseDate(year, month, day);
        
        day += n;
        
        while(day > getDaysInMonth(year, month)) {
            day -= getDaysInMonth(year, month);
            month++;
            if(month > 12) {
                month = 1;
                year++;
            }
        }
        
        formatDate(year, month, day);
        return *this;
    }
    
    // 计算n天以前的日期
    Date& Sub(int n) {
        if(n < 0) {
            return Add(-n);
        }
        
        int year, month, day;
        parseDate(year, month, day);
        
        day -= n;
        
        while(day < 1) {
            month--;
            if(month < 1) {
                month = 12;
                year--;
            }
            day += getDaysInMonth(year, month);
        }
        
        formatDate(year, month, day);
        return *this;
    }
    
    // 输出Date对象的数据
    void Display() const {
        cout << pYMD << endl;
    }
    
    // 获取日期字符串
    const char* getDate() const {
        return pYMD;
    }
};

int main() {
    cout << "测试Date类" << endl;
    cout << endl;
    
    // 测试带参数构造函数
    cout << "1. 带参数构造函数测试:" << endl;
    Date d1(2026, 6, 12);
    cout << "d1 = ";
    d1.Display();
    
    // 测试拷贝构造函数
    cout << "\n2. 拷贝构造函数测试:" << endl;
    Date d2(d1);
    cout << "d2 (拷贝d1) = ";
    d2.Display();
    
    // 测试默认构造函数
    cout << "\n3. 默认构造函数测试:" << endl;
    Date d3;
    cout << "d3 = ";
    d3.Display();
    
    // 测试字符串参数构造函数
    cout << "\n4. 字符串参数构造函数测试:" << endl;
    Date d4("2025年01月01日");
    cout << "d4 = ";
    d4.Display();
    
    // 测试赋值运算符重载
    cout << "\n5. 赋值运算符重载测试:" << endl;
    Date d5;
    d5 = d1;
    cout << "d5 = d1 = ";
    d5.Display();
    
    // 测试Add函数
    cout << "\n6. Add函数测试 (计算n天以后):" << endl;
    Date d6(2026, 6, 12);
    cout << "d6 = ";
    d6.Display();
    d6.Add(10);
    cout << "d6 + 10天 = ";
    d6.Display();
    
    Date d7(2026, 12, 25);
    cout << "\nd7 = ";
    d7.Display();
    d7.Add(15);
    cout << "d7 + 15天 = ";
    d7.Display();
    
    Date d8(2024, 2, 28);
    cout << "\nd8 = ";
    d8.Display();
    d8.Add(3);
    cout << "d8 + 3天 = ";
    d8.Display();
    
    // 测试跨年情况
    Date d9(2026, 12, 30);
    cout << "\nd9 = ";
    d9.Display();
    d9.Add(10);
    cout << "d9 + 10天 = ";
    d9.Display();
    
    // 测试Sub函数
    cout << "\n7. Sub函数测试 (计算n天以前):" << endl;
    Date d10(2026, 6, 12);
    cout << "d10 = ";
    d10.Display();
    d10.Sub(5);
    cout << "d10 - 5天 = ";
    d10.Display();
    
    Date d11(2026, 1, 5);
    cout << "\nd11 = ";
    d11.Display();
    d11.Sub(10);
    cout << "d11 - 10天 = ";
    d11.Display();
    
    Date d12(2024, 3, 1);
    cout << "\nd12 = ";
    d12.Display();
    d12.Sub(3);
    cout << "d12 - 3天 = ";
    d12.Display();
    
    // 测试链式调用
    cout << "\n8. 链式调用测试:" << endl;
    Date d13(2026, 6, 1);
    cout << "d13 = ";
    d13.Display();
    d13.Add(5).Sub(3).Add(10);
    cout << "d13 +5天 -3天 +10天 = ";
    d13.Display();
    
    // 测试连续操作
    cout << "\n9. 连续操作测试:" << endl;
    Date d14(2026, 12, 20);
    cout << "d14 = ";
    d14.Display();
    d14.Add(20);
    cout << "d14 +20天 = ";
    d14.Display();
    d14.Sub(15);
    cout << "d14 -15天 = ";
    d14.Display();
    
    // 测试边界情况
    cout << "\n10. 边界情况测试:" << endl;
    Date d15(2026, 2, 28);
    cout << "d15 = ";
    d15.Display();
    d15.Add(1);
    cout << "d15 +1天 = ";
    d15.Display();
    
    Date d16(2026, 3, 1);
    cout << "\nd16 = ";
    d16.Display();
    d16.Sub(1);
    cout << "d16 -1天 = ";
    d16.Display();
    
    return 0;
}