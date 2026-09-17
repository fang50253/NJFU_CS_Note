// assignment:
// 设计一个学生类CStudent，其结构如下：
// 1.私有数据成员：No（学号），Name（姓名），DegChinese（语文成绩），DegMath（数学成绩），DegEnglish（英语成绩），两个数据成员 Sum（总分）和Average（平均分）；
// 2.重载构造函数，实现对类实例对象的带参数初始化和无参数初始化；
// 3.公有成员函数 SetData（）；实现键盘随机输入对数据成员赋值；
// 4.公有成员函数 Display（）；实现屏幕输出数据成员；
// 5.公有成员函数 Average（）；用于计算学生个人平均分；

#include<iostream>
#include<string>
#include<algorithm>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::swap;

// 学生类
class CStudent {
private:
    string No;        // 学号
    string Name;      // 姓名
    float DegChinese; // 语文成绩
    float DegMath;    // 数学成绩
    float DegEnglish; // 英语成绩
    float Sum;        // 总分
    float Average;    // 平均分

public:
    // 无参数构造函数
    CStudent() {
        No = "";
        Name = "";
        DegChinese = 0;
        DegMath = 0;
        DegEnglish = 0;
        Sum = 0;
        Average = 0;
    }

    // 带参数构造函数
    CStudent(string no, string name, float chinese, float math, float english) {
        No = no;
        Name = name;
        DegChinese = chinese;
        DegMath = math;
        DegEnglish = english;
        Sum = DegChinese + DegMath + DegEnglish;
        Average = Sum / 3;
    }

    // 键盘输入赋值
    void SetData() {
        cout << "请输入学号: ";
        cin >> No;
        cout << "请输入姓名: ";
        cin >> Name;
        cout << "请输入语文成绩: ";
        cin >> DegChinese;
        cout << "请输入数学成绩: ";
        cin >> DegMath;
        cout << "请输入英语成绩: ";
        cin >> DegEnglish;
        Sum = DegChinese + DegMath + DegEnglish;
        Average = Sum / 3;
    }

    // 计算个人平均分
    void CalAverage() {
        Average = Sum / 3;
    }

    // 输出数据成员
    void Display() {
        cout << "学号: " << No << "\t姓名: " << Name << "\t语文: " << DegChinese
             << "\t数学: " << DegMath << "\t英语: " << DegEnglish
             << "\t总分: " << Sum << "\t平均分: " << Average << endl;
    }

    // 获取平均分（用于排序）
    float getAverage() const {
        return Average;
    }

    // 获取总分
    float getSum() const {
        return Sum;
    }

    // 获取各科成绩（用于统计）
    float getChinese() const { return DegChinese; }
    float getMath() const { return DegMath; }
    float getEnglish() const { return DegEnglish; }
    string getName() const { return Name; }
    string getNo() const { return No; }
};

// 统计类
class CStatistic {
private:
    int Nums;               // 学生人数
    float AveChinese;       // 语文总评成绩
    float AveMath;          // 数学总评成绩
    float AveEnglish;       // 英语总评成绩
    CStudent* StuArray;     // 学生对象数组指针

public:
    // 构造函数
    CStatistic(int n) {
        Nums = n;
        AveChinese = 0;
        AveMath = 0;
        AveEnglish = 0;
        StuArray = new CStudent[Nums];
    }

    // 析构函数
    ~CStatistic() {
        delete[] StuArray;
    }

    // 输入所有学生数据
    void InputData() {
        for(int i = 0; i < Nums; i++) {
            cout << "\n===== 输入第 " << i+1 << " 个学生信息 =====" << endl;
            StuArray[i].SetData();
        }
    }

    // 计算全班平均分（静态成员函数）
    static void Average(CStatistic& stat) {
        float sumChinese = 0, sumMath = 0, sumEnglish = 0;
        for(int i = 0; i < stat.Nums; i++) {
            sumChinese += stat.StuArray[i].getChinese();
            sumMath += stat.StuArray[i].getMath();
            sumEnglish += stat.StuArray[i].getEnglish();
        }
        stat.AveChinese = sumChinese / stat.Nums;
        stat.AveMath = sumMath / stat.Nums;
        stat.AveEnglish = sumEnglish / stat.Nums;
        
        cout << "\n===== 全班总评成绩 =====" << endl;
        cout << "语文平均分: " << stat.AveChinese << endl;
        cout << "数学平均分: " << stat.AveMath << endl;
        cout << "英语平均分: " << stat.AveEnglish << endl;
    }

    // 按照平均分从高到低排序
    void Sort() {
        for(int i = 0; i < Nums - 1; i++) {
            for(int j = 0; j < Nums - i - 1; j++) {
                if(StuArray[j].getAverage() < StuArray[j+1].getAverage()) {
                    swap(StuArray[j], StuArray[j+1]);
                }
            }
        }
        cout << "\n已按平均分从高到低排序！" << endl;
    }

    // 输出所有学生信息
    void Display() {
        cout << "\n===== 学生成绩一览表 =====" << endl;
        cout << "总人数: " << Nums << endl;
        for(int i = 0; i < Nums; i++) {
            cout << "第 " << i+1 << " 名: ";
            StuArray[i].Display();
        }
    }

    // 获取学生数组（用于外部访问）
    CStudent* getStuArray() { return StuArray; }
    int getNums() { return Nums; }
};

int main() {
    int n;
    cout << "请输入学生人数: ";
    cin >> n;
    
    // 定义指向CStatistic对象的指针
    CStatistic* pStatistic = new CStatistic(n);
    
    // 输入学生数据
    pStatistic->InputData();
    
    // 显示排序前的学生信息
    pStatistic->Display();
    
    // 按平均分排序
    pStatistic->Sort();
    
    // 显示排序后的学生信息
    pStatistic->Display();
    
    // 计算全班平均分（静态成员函数调用）
    CStatistic::Average(*pStatistic);
    
    // 释放内存
    delete pStatistic;
    
    return 0;
}