//assignment：
//设计一个点类Point，其结构如下：
// 1.Point类表示二维平面点的集合，数据成员由点的坐标值表示
// 2.三个重载构造函数：
// 3.一个是无参数的构造函数
// 4.一个是带坐标值参数的构造函数，实现对数据成员的初始化
// 5.一个是copy构造函数，实现用一个对象初始化本对象
// 两个重载成员函数：
// 1.void offset(int, int)；实现点的偏移，参数是偏移量
// 2.void offset(Point &)；实现点的偏移，参数Point类对象是偏移量
// 8个运算符重载函数：
// 1.bool operator==(Point &)；判断两个点对象是否相等
// 2.bool operator!=(Point &)；判断两个点对象是否不相等
// 3.void operator+=(Point &)；将两个点对象相加
// 4.void operator-=(Point &)；将两个点对象相减
// 5.void operator++()；将当前对象自增1（前缀）
// 6.void operator++(int k)；将当前对象自增10（后缀）
// 7.void operator--()；将当前对象自减1（前缀）
// 8.void operator--(int k)；将当前对象自减10（后缀）
// 9.friend Point& operator+(Point &, Point &)；将两个点对象相加
// 10.friend Point& operator-(Point &, Point &)；将两个点对象相减
// 两个成员函数提供实例对象对私有数据的访问：
// 1.int GetX()
// 2.int GetY()
// 公有成员函数 void Display()；输出对象的数据成员

#include<iostream>
using std::cout;
using std::cin;
using std::endl;

class Point {
private:
    int x;  // x坐标
    int y;  // y坐标

public:
    // 无参数的构造函数
    Point() {
        x = 0;
        y = 0;
    }
    
    // 带坐标值参数的构造函数
    Point(int xVal, int yVal) {
        x = xVal;
        y = yVal;
    }
    
    // copy构造函数
    Point(const Point& ob) {
        x = ob.x;
        y = ob.y;
    }
    
    // 析构函数
    ~Point() {}
    
    // 实现点的偏移，参数是偏移量
    void offset(int dx, int dy) {
        x += dx;
        y += dy;
    }
    
    // 实现点的偏移，参数Point类对象是偏移量
    void offset(Point& p) {
        x += p.x;
        y += p.y;
    }
    
    // 判断两个点对象是否相等
    bool operator==(Point& p) {
        return (x == p.x && y == p.y);
    }
    
    // 判断两个点对象是否不相等
    bool operator!=(Point& p) {
        return (x != p.x || y != p.y);
    }
    
    // 将两个点对象相加
    void operator+=(Point& p) {
        x += p.x;
        y += p.y;
    }
    
    // 将两个点对象相减
    void operator-=(Point& p) {
        x -= p.x;
        y -= p.y;
    }
    
    // 将当前对象自增1（前缀）
    void operator++() {
        x += 1;
        y += 1;
    }
    
    // 将当前对象自增10（后缀）
    void operator++(int k) {
        x += 10;
        y += 10;
    }
    
    // 将当前对象自减1（前缀）
    void operator--() {
        x -= 1;
        y -= 1;
    }
    
    // 将当前对象自减10（后缀）
    void operator--(int k) {
        x -= 10;
        y -= 10;
    }
    
    // 将两个点对象相加（友元函数）
    friend Point& operator+(Point& p1, Point& p2);
    
    // 将两个点对象相减（友元函数）
    friend Point& operator-(Point& p1, Point& p2);
    
    // 获取x坐标
    int GetX() {
        return x;
    }
    
    // 获取y坐标
    int GetY() {
        return y;
    }
    
    // 输出对象的数据成员
    void Display() {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

// 将两个点对象相加
Point& operator+(Point& p1, Point& p2) {
    Point* p = new Point(p1.x + p2.x, p1.y + p2.y);
    return *p;
}

// 将两个点对象相减
Point& operator-(Point& p1, Point& p2) {
    Point* p = new Point(p1.x - p2.x, p1.y - p2.y);
    return *p;
}

int main() {
    cout << "测试Point类" << endl;
    cout << endl;
    
    // 测试无参数构造函数
    cout << "1. 无参数构造函数测试:" << endl;
    Point p1;
    cout << "p1 = ";
    p1.Display();
    
    // 测试带参数构造函数
    cout << "\n2. 带参数构造函数测试:" << endl;
    Point p2(3, 4);
    cout << "p2(3, 4) = ";
    p2.Display();
    
    // 测试拷贝构造函数
    cout << "\n3. 拷贝构造函数测试:" << endl;
    Point p3(p2);
    cout << "p3(p2) = ";
    p3.Display();
    
    // 测试offset函数（偏移量）
    cout << "\n4. offset函数测试 (偏移量):" << endl;
    Point p4(1, 2);
    cout << "p4 = ";
    p4.Display();
    p4.offset(5, 3);
    cout << "p4.offset(5, 3) = ";
    p4.Display();
    
    // 测试offset函数（点对象）
    cout << "\n5. offset函数测试 (点对象):" << endl;
    Point p5(2, 1);
    Point p6(3, 2);
    cout << "p5 = ";
    p5.Display();
    cout << "p6 = ";
    p6.Display();
    p5.offset(p6);
    cout << "p5.offset(p6) = ";
    p5.Display();
    
    // 测试相等运算符
    cout << "\n6. 相等运算符测试:" << endl;
    Point p7(1, 1);
    Point p8(1, 1);
    Point p9(2, 2);
    cout << "p7 = ";
    p7.Display();
    cout << "p8 = ";
    p8.Display();
    cout << "p9 = ";
    p9.Display();
    cout << "p7 == p8 : " << (p7 == p8 ? "true" : "false") << endl;
    cout << "p7 == p9 : " << (p7 == p9 ? "true" : "false") << endl;
    
    // 测试不等运算符
    cout << "\n7. 不等运算符测试:" << endl;
    cout << "p7 != p8 : " << (p7 != p8 ? "true" : "false") << endl;
    cout << "p7 != p9 : " << (p7 != p9 ? "true" : "false") << endl;
    
    // 测试+=运算符
    cout << "\n8. +=运算符测试:" << endl;
    Point p10(1, 2);
    Point p11(3, 4);
    cout << "p10 = ";
    p10.Display();
    cout << "p11 = ";
    p11.Display();
    p10 += p11;
    cout << "p10 += p11 = ";
    p10.Display();
    
    // 测试-=运算符
    cout << "\n9. -=运算符测试:" << endl;
    Point p12(5, 6);
    Point p13(2, 3);
    cout << "p12 = ";
    p12.Display();
    cout << "p13 = ";
    p13.Display();
    p12 -= p13;
    cout << "p12 -= p13 = ";
    p12.Display();
    
    // 测试前缀++运算符
    cout << "\n10. 前缀++运算符测试:" << endl;
    Point p14(1, 1);
    cout << "p14 = ";
    p14.Display();
    ++p14;
    cout << "++p14 = ";
    p14.Display();
    
    // 测试后缀++运算符
    cout << "\n11. 后缀++运算符测试:" << endl;
    Point p15(1, 1);
    cout << "p15 = ";
    p15.Display();
    p15++;
    cout << "p15++ = ";
    p15.Display();
    
    // 测试前缀--运算符
    cout << "\n12. 前缀--运算符测试:" << endl;
    Point p16(10, 10);
    cout << "p16 = ";
    p16.Display();
    --p16;
    cout << "--p16 = ";
    p16.Display();
    
    // 测试后缀--运算符
    cout << "\n13. 后缀--运算符测试:" << endl;
    Point p17(10, 10);
    cout << "p17 = ";
    p17.Display();
    p17--;
    cout << "p17-- = ";
    p17.Display();
    
    // 测试+运算符（友元函数）
    cout << "\n14. +运算符测试:" << endl;
    Point p18(1, 2);
    Point p19(3, 4);
    cout << "p18 = ";
    p18.Display();
    cout << "p19 = ";
    p19.Display();
    Point p20 = operator+(p18, p19);
    cout << "p18 + p19 = ";
    p20.Display();
    
    // 测试-运算符（友元函数）
    cout << "\n15. -运算符测试:" << endl;
    Point p21(5, 6);
    Point p22(2, 3);
    cout << "p21 = ";
    p21.Display();
    cout << "p22 = ";
    p22.Display();
    Point p23 = operator-(p21, p22);
    cout << "p21 - p22 = ";
    p23.Display();
    
    // 测试GetX和GetY
    cout << "\n16. GetX和GetY测试:" << endl;
    Point p24(7, 8);
    cout << "p24 = ";
    p24.Display();
    cout << "p24.GetX() = " << p24.GetX() << endl;
    cout << "p24.GetY() = " << p24.GetY() << endl;
    
    // 综合测试
    cout << "\n17. 综合测试:" << endl;
    Point p25(0, 0);
    Point p26(5, 5);
    Point p27(2, 3);
    cout << "初始状态:" << endl;
    cout << "p25 = ";
    p25.Display();
    cout << "p26 = ";
    p26.Display();
    cout << "p27 = ";
    p27.Display();
    
    p25 += p26;
    cout << "\np25 += p26 -> p25 = ";
    p25.Display();
    
    p25 -= p27;
    cout << "p25 -= p27 -> p25 = ";
    p25.Display();
    
    ++p25;
    cout << "++p25 -> p25 = ";
    p25.Display();
    
    p25--;
    cout << "p25-- -> p25 = ";
    p25.Display();
    
    Point p28 = operator+(p25, p26);
    cout << "\np25 + p26 = ";
    p28.Display();
    
    return 0;
}