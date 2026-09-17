// assignment
// 主函数设计要求：
// 1.定义一个指向CStatistic对象的指针 pStatistic，实现对象的初始化或赋值；
// 2.输出格式如下
// 学号｜姓名｜语文｜数学｜英语｜平均分｜总分

#include<iostream>
#include<string>
#include<iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;
using std::left;
using std::right;

// 学生类
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

    void Display() const {
        cout << left << setw(8) << No 
             << left << setw(8) << Name
             << right << setw(6) << DegChinese
             << right << setw(6) << DegMath
             << right << setw(6) << DegEnglish
             << right << setw(8) << Average
             << right << setw(6) << Sum << endl;
    }

    float getAverage() const { return Average; }
    float getSum() const { return Sum; }
    float getChinese() const { return DegChinese; }
    float getMath() const { return DegMath; }
    float getEnglish() const { return DegEnglish; }
    string getName() const { return Name; }
    string getNo() const { return No; }
};

// 统计类
class CStatistic {
private:
    int Nums;
    float AveChinese;
    float AveMath;
    float AveEnglish;
    CStudent* StuArray;

public:
    CStatistic(int n) {
        Nums = n;
        AveChinese = 0;
        AveMath = 0;
        AveEnglish = 0;
        StuArray = new CStudent[Nums];
    }

    ~CStatistic() {
        delete[] StuArray;
    }

    void InputData() {
        for(int i = 0; i < Nums; i++) {
            cout << "\n===== 输入第 " << i+1 << " 个学生信息 =====" << endl;
            StuArray[i].SetData();
        }
    }

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
    }

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
    }

    void Display() const {
        cout << "\n" << string(70, '=') << endl;
        cout << left << setw(8) << "学号" 
             << left << setw(8) << "姓名"
             << right << setw(6) << "语文"
             << right << setw(6) << "数学"
             << right << setw(6) << "英语"
             << right << setw(8) << "平均分"
             << right << setw(6) << "总分" << endl;
        cout << string(70, '-') << endl;
        
        for(int i = 0; i < Nums; i++) {
            StuArray[i].Display();
        }
        
        cout << string(70, '-') << endl;
        cout << left << setw(8) << "总评"
             << left << setw(8) << ""
             << right << setw(6) << AveChinese
             << right << setw(6) << AveMath
             << right << setw(6) << AveEnglish << endl;
        cout << string(70, '=') << endl;
    }

    CStudent* getStuArray() { return StuArray; }
    int getNums() const { return Nums; }
    float getAveChinese() const { return AveChinese; }
    float getAveMath() const { return AveMath; }
    float getAveEnglish() const { return AveEnglish; }
};

int main() {
    int n;
    cout << "请输入学生人数: ";
    cin >> n;
    cin.ignore(); // 清除缓冲区
    
    // 1. 定义一个指向CStatistic对象的指针 pStatistic，实现对象的初始化或赋值
    CStatistic* pStatistic = new CStatistic(n);
    
    // 输入学生数据
    pStatistic->InputData();
    
    // 按平均分排序
    pStatistic->Sort();
    
    // 计算全班平均分（静态成员函数调用）
    CStatistic::Average(*pStatistic);
    
    // 2. 按照指定格式输出
    pStatistic->Display();
    
    // 释放内存
    delete pStatistic;

    return 0;
}