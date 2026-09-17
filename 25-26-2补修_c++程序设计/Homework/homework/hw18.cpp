// assignment
// 设计评选优秀教师和优秀学生的程序，其类结构和派生关系如下图所示。当输入一系列教师和学生的记录后，将优秀教师和学生的姓名列出来。
// Base类
// 1.char Name[10]; // 姓名
// 2.void GetName(); // 输入姓名
// 3.void Display();
// 4.virtual bool IsGood() = 0; // 纯虚函数
// Teacher类（继承自Base）
// 1.int Paper; // 论文数
// 2.void GetPaper(); // 输入论文数
// 3.void Display();
// 4.bool IsGood(); // 评选标准：论文数 > 5
// Student类（继承自Base）
// 1.int Degree; // 成绩（或平均分）
// 2.void GetDegree(); // 输入成绩
// 3.void Display();
// 4.bool IsGood(); // 评选标准：成绩 > 90

#include<iostream>
#include<cstring>
using std::cout;
using std::cin;
using std::endl;

// 抽象基类 Base
class Base {
protected:
    char Name[10];  // 姓名

public:
    // 构造函数
    Base() {
        Name[0] = '\0';
    }
    
    // 析构函数
    virtual ~Base() {}
    
    // 输入姓名
    void GetName() {
        cout << "请输入姓名: ";
        cin >> Name;
    }
    
    // 显示信息
    virtual void Display() {
        cout << "姓名: " << Name << endl;
    }
    
    // 纯虚函数，判断是否优秀
    virtual bool IsGood() = 0;
};

// Teacher类，继承自Base
class Teacher : public Base {
private:
    int Paper;  // 论文数

public:
    // 构造函数
    Teacher() : Base() {
        Paper = 0;
    }
    
    // 输入论文数
    void GetPaper() {
        cout << "请输入论文数: ";
        cin >> Paper;
    }
    
    // 显示信息
    void Display() override {
        Base::Display();
        cout << "论文数: " << Paper << endl;
    }
    
    // 判断是否优秀教师（论文数 > 5）
    bool IsGood() override {
        return Paper > 5;
    }
    
    // 获取姓名
    char* GetName() {
        return Name;
    }
};

// Student类，继承自Base
class Student : public Base {
private:
    int Degree;  // 成绩

public:
    // 构造函数
    Student() : Base() {
        Degree = 0;
    }
    
    // 输入成绩
    void GetDegree() {
        cout << "请输入成绩: ";
        cin >> Degree;
    }
    
    // 显示信息
    void Display() override {
        Base::Display();
        cout << "成绩: " << Degree << endl;
    }
    
    // 判断是否优秀学生（成绩 > 90）
    bool IsGood() override {
        return Degree > 90;
    }
    
    // 获取姓名
    char* GetName() {
        return Name;
    }
};

int main() {
    int n;
    int teacherCount = 0;
    int studentCount = 0;
    
    cout << "请输入教师人数: ";
    cin >> teacherCount;
    
    cout << "请输入学生人数: ";
    cin >> studentCount;
    
    // 创建动态数组存储基类指针
    Base** persons = new Base*[teacherCount + studentCount];
    
    // 输入教师信息
    cout << "\n===== 输入教师信息 =====" << endl;
    for(int i = 0; i < teacherCount; i++) {
        cout << "\n第 " << i + 1 << " 位教师:" << endl;
        Teacher* t = new Teacher();
        t->Base::GetName();
        t->GetPaper();
        persons[i] = t;
    }
    
    // 输入学生信息
    cout << "\n===== 输入学生信息 =====" << endl;
    for(int i = 0; i < studentCount; i++) {
        cout << "\n第 " << i + 1 << " 位学生:" << endl;
        Student* s = new Student();
        s->Base::GetName();
        s->GetDegree();
        persons[teacherCount + i] = s;
    }
    
    // 显示所有人员信息
    cout << "\n===== 所有人员信息 =====" << endl;
    for(int i = 0; i < teacherCount + studentCount; i++) {
        cout << "\n第 " << i + 1 << " 位:" << endl;
        persons[i]->Display();
    }
    
    // 评选优秀教师和优秀学生
    cout << "\n===== 优秀教师 =====" << endl;
    bool hasGoodTeacher = false;
    for(int i = 0; i < teacherCount; i++) {
        if(persons[i]->IsGood()) {
            Teacher* t = dynamic_cast<Teacher*>(persons[i]);
            if(t != nullptr) {
                cout << "优秀教师: " << t->GetName() << endl;
                hasGoodTeacher = true;
            }
        }
    }
    if(!hasGoodTeacher) {
        cout << "没有优秀教师" << endl;
    }
    
    cout << "\n===== 优秀学生 =====" << endl;
    bool hasGoodStudent = false;
    for(int i = teacherCount; i < teacherCount + studentCount; i++) {
        if(persons[i]->IsGood()) {
            Student* s = dynamic_cast<Student*>(persons[i]);
            if(s != nullptr) {
                cout << "优秀学生: " << s->GetName() << endl;
                hasGoodStudent = true;
            }
        }
    }
    if(!hasGoodStudent) {
        cout << "没有优秀学生" << endl;
    }
    
    // 释放内存
    for(int i = 0; i < teacherCount + studentCount; i++) {
        delete persons[i];
    }
    delete[] persons;
    
    return 0;
}