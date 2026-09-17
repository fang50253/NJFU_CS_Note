//assignment：
// 设计一个虚基类 Person，派生出父亲类 Father、母亲类 Mother，再间接派生出孩子类 Child；其主要数据包括姓、名、年龄、性别。孩子类用父类的姓。要求如下：
// 重载构造函数初始化数据成员
// 公有成员函数 void SetData(...)：实现数据赋值
// 设计一个 Person 对象指针数组，完成初始化；并按照年龄从大到小排序输出，格式如下：
// 姓名	年龄	性别	父亲	母亲
// 王军	49	男	不详	不详
// 李丽	47	女	不详	不详
// 张涵	35	男	不详	不详
// 刘美	32	女	不详	不详
// 王仪	17	女	王军	李丽

#include<iostream>
#include<string>
#include<iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::left;
using std::setw;
using std::swap;

// 虚基类 Person
class Person {
protected:
    string firstName;   // 姓
    string lastName;    // 名
    int age;            // 年龄
    string gender;      // 性别

public:
    // 构造函数
    Person() {
        firstName = "";
        lastName = "";
        age = 0;
        gender = "";
    }
    
    Person(string fname, string lname, int a, string g) {
        firstName = fname;
        lastName = lname;
        age = a;
        gender = g;
    }
    
    // 析构函数
    virtual ~Person() {}
    
    // 设置数据
    virtual void SetData(string fname, string lname, int a, string g) {
        firstName = fname;
        lastName = lname;
        age = a;
        gender = g;
    }
    
    // 获取年龄
    int getAge() const {
        return age;
    }
    
    // 获取姓名
    string getFullName() const {
        return firstName + lastName;
    }
    
    string getFirstName() const {
        return firstName;
    }
    
    string getLastName() const {
        return lastName;
    }
    
    string getGender() const {
        return gender;
    }
    
    // 显示信息
    virtual void Display() const {
        cout << left << setw(10) << getFullName()
             << setw(6) << age
             << setw(8) << gender;
    }
};

// 父亲类
class Father : virtual public Person {
public:
    Father() : Person() {}
    
    Father(string fname, string lname, int a, string g) 
        : Person(fname, lname, a, g) {}
    
    void SetData(string fname, string lname, int a, string g) override {
        Person::SetData(fname, lname, a, g);
    }
};

// 母亲类
class Mother : virtual public Person {
public:
    Mother() : Person() {}
    
    Mother(string fname, string lname, int a, string g) 
        : Person(fname, lname, a, g) {}
    
    void SetData(string fname, string lname, int a, string g) override {
        Person::SetData(fname, lname, a, g);
    }
};

// 孩子类（间接派生）
class Child : public Father, public Mother {
private:
    string fatherName;   // 父亲姓名
    string motherName;   // 母亲姓名

public:
    Child() : Person(), Father(), Mother() {
        fatherName = "";
        motherName = "";
    }
    
    Child(string fname, string lname, int a, string g, 
          string fName, string mName) 
        : Person(fname, lname, a, g), Father(fname, lname, a, g), 
          Mother(fname, lname, a, g) {
        fatherName = fName;
        motherName = mName;
    }
    
    void SetData(string fname, string lname, int a, string g, 
                 string fName, string mName) {
        Person::SetData(fname, lname, a, g);
        fatherName = fName;
        motherName = mName;
    }
    
    void SetData(string fname, string lname, int a, string g) override {
        Person::SetData(fname, lname, a, g);
        fatherName = "不详";
        motherName = "不详";
    }
    
    string getFatherName() const {
        return fatherName;
    }
    
    string getMotherName() const {
        return motherName;
    }
    
    void Display() const override {
        cout << left << setw(10) << getFullName()
             << setw(6) << age
             << setw(8) << gender
             << setw(10) << fatherName
             << setw(10) << motherName << endl;
    }
};

// 排序函数（按年龄从大到小）
void SortByAge(Person** arr, int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j]->getAge() < arr[j+1]->getAge()) {
                Person* temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    // 设计 Person 对象指针数组
    Person* persons[5];
    
    // 初始化数组元素
    persons[0] = new Father("王", "军", 49, "男");
    persons[1] = new Mother("李", "丽", 47, "女");
    persons[2] = new Father("张", "涵", 35, "男");
    persons[3] = new Mother("刘", "美", 32, "女");
    
    // 孩子类需要设置父亲和母亲信息
    Child* child = new Child("王", "仪", 17, "女", "王军", "李丽");
    persons[4] = child;
    
    // 按年龄从大到小排序
    SortByAge(persons, 5);
    
    // 输出表头
    cout << left << setw(10) << "姓名"
         << setw(6) << "年龄"
         << setw(8) << "性别"
         << setw(10) << "父亲"
         << setw(10) << "母亲" << endl;
    cout << "----------------------------------------" << endl;
    
    // 输出排序后的结果
    for(int i = 0; i < 5; i++) {
        // 判断是否为孩子类，以便输出父亲和母亲信息
        Child* c = dynamic_cast<Child*>(persons[i]);
        if(c != nullptr) {
            c->Display();
        } else {
            cout << left << setw(10) << persons[i]->getFullName()
                 << setw(6) << persons[i]->getAge()
                 << setw(8) << persons[i]->getGender()
                 << setw(10) << "不详"
                 << setw(10) << "不详" << endl;
        }
    }
    
    // 释放内存
    for(int i = 0; i < 5; i++) {
        delete persons[i];
    }
    
    return 0;
}