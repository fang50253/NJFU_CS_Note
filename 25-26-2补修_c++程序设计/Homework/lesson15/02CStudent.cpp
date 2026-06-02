
// 设计一个学生类CStudent，其结构如下：
// 	私有数据成员Name（学生姓名）、Degree（成绩）、Level[7]（成绩等级）；
// 	构造函数对数据成员初始化；
// 	设计一个CStudents的友元类CProcess，其结构包含两个成员函数：
// 	void Transform(CStudent& s)；实现对s的数据成员Level的判断其成绩的等级，：>=90为优秀；80～89为良好；70～79为中等；60～69为及格；< 60为不及格；
// 	void Display(CStudent& s)输出s成绩的等级；
// 	输出结果如下：
// 姓名	成绩	等级
// Mary	78	中等
// Jack	93	优秀
// Mike	54	不及格
// John	88	良好


#include<bits/stdc++.h>
class CStudent{
private:
    std::string Name;
    int Degree;
    char Level[7];
public:
    CStudent(std::string name, int degree){
        Name = name;
        Degree = degree;
    }
    friend class CProcess;  // 声明友元类
};

class CProcess{
public:
    void Transform(CStudent& stu);
    void Display(CStudent& stu);
};

void CProcess::Transform(CStudent& stu){
    if(stu.Degree>=90){
        strcpy(stu.Level, "优秀");
    }
    else if(stu.Degree>=80){
        strcpy(stu.Level, "良好");
    }
    else if(stu.Degree>=70){
        strcpy(stu.Level, "中等");
    }
    else if(stu.Degree>=60){
        strcpy(stu.Level, "及格");
    }
    else{
        strcpy(stu.Level, "不及格");
    }
}

void CProcess::Display(CStudent& stu){
    std::cout << stu.Name << "\t" << stu.Degree << "\t" << stu.Level << std::endl;
}

int main(){
    std::cout << "姓名\t成绩\t等级" << std::endl;
    
    // 创建学生对象
    CStudent stu1("Mary", 78);
    CStudent stu2("Jack", 93);
    CStudent stu3("Mike", 54);
    CStudent stu4("John", 88);
    
    // 创建处理对象
    CProcess processor;
    
    // 处理并显示每个学生
    processor.Transform(stu1);
    processor.Display(stu1);
    
    processor.Transform(stu2);
    processor.Display(stu2);
    
    processor.Transform(stu3);
    processor.Display(stu3);
    
    processor.Transform(stu4);
    processor.Display(stu4);
    
    return 0;
}