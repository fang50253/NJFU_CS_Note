// assignment
// 设计一个统计类CStatistic，其结构如下：
// •私有数据成员：Nums（学生人数），AveChinese（语文总评成绩），AveMath（数学总评成绩），AveEnglish（英语总评成绩），StuArray（学生对象数组）；
// •公有静态成员函数 Average（）；用于计算全班平均分；
// •公有成员函数 Sort（）；实现学生对象数组中的对象按照平均分（从高到低）排序；
// •公有成员函数 Display（）；实现屏幕输出数据成员；

#include<iostream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

// 学生类（前置声明）
class CStudent {
private:
    string No;
    string Name;
    float DegChinese;
    float DegMath;
    float DegEnglish;
    float Sum;
    float Average;

public:
    CStudent() {
        No = "";
        Name = "";
        DegChinese = 0;
        DegMath = 0;
        DegEnglish = 0;
        Sum = 0;
        Average = 0;
    }

    CStudent(string no, string name, float chinese, float math, float english) {
        No = no;
        Name = name;
        DegChinese = chinese;
        DegMath = math;
        DegEnglish = english;
        Sum = DegChinese + DegMath + DegEnglish;
        Average = Sum / 3;
    }

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

    void CalAverage() {
        Average = Sum / 3;
    }

    void Display() {
        cout << "学号: " << No << "\t姓名: " << Name 
             << "\t语文: " << DegChinese << "\t数学: " << DegMath 
             << "\t英语: " << DegEnglish << "\t总分: " << Sum 
             << "\t平均分: " << Average << endl;
    }

    float getAverage() const { return Average; }
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
    CStudent* StuArray;     // 学生对象数组

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

    // 公有静态成员函数：计算全班平均分
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
        cout << "全班总平均分: " << (stat.AveChinese + stat.AveMath + stat.AveEnglish) / 3 << endl;
    }

    // 公有成员函数：按照平均分从高到低排序
    void Sort() {
        for(int i = 0; i < Nums - 1; i++) {
            for(int j = 0; j < Nums - i - 1; j++) {
                if(StuArray[j].getAverage() < StuArray[j+1].getAverage()) {
                    CStudent temp = StuArray[j];
                    StuArray[j] = StuArray[j+1];
                    StuArray[j+1] = temp;
                }
            }
        }
        cout << "\n已按平均分从高到低排序！" << endl;
    }

    // 公有成员函数：输出所有数据成员
    void Display() {
        cout << "\n===== 学生成绩一览表 =====" << endl;
        cout << "学生总人数: " << Nums << endl;
        cout << "语文总评成绩: " << AveChinese << endl;
        cout << "数学总评成绩: " << AveMath << endl;
        cout << "英语总评成绩: " << AveEnglish << endl;
        cout << "\n学生详细信息:" << endl;
        
        for(int i = 0; i < Nums; i++) {
            cout << "第 " << i+1 << " 名: ";
            StuArray[i].Display();
        }
    }

    // 辅助函数：获取学生数组
    CStudent* getStuArray() { return StuArray; }
    int getNums() { return Nums; }
    float getAveChinese() { return AveChinese; }
    float getAveMath() { return AveMath; }
    float getAveEnglish() { return AveEnglish; }
};

int main() {
    int n;
    cout << "请输入学生人数: ";
    cin >> n;
    
    // 创建统计类对象
    CStatistic* pStatistic = new CStatistic(n);
    
    // 输入学生数据
    pStatistic->InputData();
    
    // 显示排序前的信息
    pStatistic->Display();
    
    // 按平均分排序
    pStatistic->Sort();
    
    // 显示排序后的信息
    pStatistic->Display();
    
    // 计算全班平均分（静态成员函数调用）
    CStatistic::Average(*pStatistic);
    
    // 再次显示包含总评成绩的信息
    pStatistic->Display();
    
    // 释放内存
    delete pStatistic;

    return 0;
}