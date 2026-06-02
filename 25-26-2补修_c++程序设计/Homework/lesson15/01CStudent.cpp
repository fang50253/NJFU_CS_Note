// 第Ⅰ题：基本练习
// 设计一个学生类CStudent，其结构如下：
// 	私有数据成员Name（学生姓名）、Degree（成绩）；
// 	构造函数对数据成员初始化；
// 	设计一个友元函数Display(CStudent&)；输出成绩的等级：>=90为优秀；80～89为良好；70～79为中等；60～69为及格；< 60为不及格；
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
public:
    CStudent(std::string name, int degree){
        Name = name;
        Degree = degree;
    }
    friend void Display(CStudent& stu);
};
void Display(CStudent& stu){
    std::cout<<stu.Name<<"\t"<<stu.Degree<<"\t";
    if(stu.Degree>=90){
        std::cout<<"优秀"<<std::endl;
    }
    else if(stu.Degree>=80){
        std::cout<<"良好"<<std::endl;
    }
    else if(stu.Degree>=70){
        std::cout<<"中等"<<std::endl;
    }
    else if(stu.Degree>=60){
        std::cout<<"及格"<<std::endl;
    }
    else{
        std::cout<<"不及格"<<std::endl;
    }
}
int main(){
    std::cout<<"姓名\t成绩\t等级"<<std::endl;
    CStudent stu1("Mary",78);
    Display(stu1);
    CStudent stu2("Jack",93);
    Display(stu2);
    CStudent stu3("Mike",54);
    Display(stu3);
    CStudent stu4("John",88);
    Display(stu4);
    return 0;
}