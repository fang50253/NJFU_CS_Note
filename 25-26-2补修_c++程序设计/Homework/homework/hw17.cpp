//assignment
// 定义一个点类Point，其结构如下：
// 1.保护数据成员 int x, y；表示二维空间点的两个坐标分量
// 2.构造函数带默认参数实现初始化数据成员 Point(int i=0, int j=0)
// 3.成员函数设置点的坐标值 void SetXY(int m, int n)
// 4.成员函数绘制当前图形 void Draw()；其实只要输出字符串“Point : (x,y)”表示当前图形是点

#include<iostream>
using std::cout;
using std::cin;
using std::endl;

class Point {
protected:
    int x;  // x坐标
    int y;  // y坐标

public:
    // 构造函数带默认参数实现初始化数据成员
    Point(int i = 0, int j = 0) {
        x = i;
        y = j;
    }
    
    // 析构函数
    ~Point() {
    }
    
    // 成员函数设置点的坐标值
    void SetXY(int m, int n) {
        x = m;
        y = n;
        cout << "点坐标已设置为(" << x << ", " << y << ")" << endl;
    }
    
    // 成员函数绘制当前图形
    void Draw() {
        cout << "Point : (" << x << ", " << y << ")" << endl;
    }
    
    // 获取x坐标
    int GetX() const {
        return x;
    }
    
    // 获取y坐标
    int GetY() const {
        return y;
    }
};

int main() {
    cout << "测试Point类" << endl;
    cout << endl;
    
    // 测试无参数构造函数（使用默认参数）
    cout << "1. 无参数构造函数测试:" << endl;
    Point p1;
    cout << "p1 = ";
    p1.Draw();
    
    // 测试带参数构造函数
    cout << "\n2. 带参数构造函数测试:" << endl;
    Point p2(3, 4);
    cout << "p2 = ";
    p2.Draw();
    
    // 测试带一个参数的构造函数
    cout << "\n3. 带一个参数构造函数测试:" << endl;
    Point p3(5);
    cout << "p3 = ";
    p3.Draw();
    
    // 测试SetXY函数
    cout << "\n4. SetXY函数测试:" << endl;
    Point p4;
    cout << "p4初始值 = ";
    p4.Draw();
    p4.SetXY(7, 8);
    cout << "p4修改后 = ";
    p4.Draw();
    
    // 测试多个对象
    cout << "\n5. 创建多个点对象:" << endl;
    Point points[3] = {Point(1, 2), Point(3, 4), Point(5, 6)};
    for(int i = 0; i < 3; i++) {
        cout << "points[" << i << "] = ";
        points[i].Draw();
    }
    
    // 测试动态创建对象
    cout << "\n6. 动态创建点对象:" << endl;
    Point* pDynamic = new Point(10, 20);
    cout << "动态创建的点 = ";
    pDynamic->Draw();
    delete pDynamic;
    
    // 测试修改坐标后绘制
    cout << "\n7. 修改坐标后绘制测试:" << endl;
    Point p5(2, 3);
    cout << "初始状态: ";
    p5.Draw();
    p5.SetXY(8, 9);
    cout << "修改后: ";
    p5.Draw();
    
    // 测试GetX和GetY
    cout << "\n8. GetX和GetY测试:" << endl;
    Point p6(4, 7);
    p6.Draw();
    cout << "p6.GetX() = " << p6.GetX() << endl;
    cout << "p6.GetY() = " << p6.GetY() << endl;
    
    cout << "\n程序结束，观察析构函数调用顺序" << endl;
    
    return 0;
}