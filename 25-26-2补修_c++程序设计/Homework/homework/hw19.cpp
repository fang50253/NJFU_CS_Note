//assignment
// 定义一个链表类List1，其结构中私有数据成员如下表：
// List1对象
// 1.L[0], L[1], L[2], ..., L[Length-1] (实际链尾节点), ..., L[Size-1] (链表节点保存在数组中) Type L[Size]; (其中Type是待定数据类型)
// 2.int size; (链表限定长度)
// 3.int Length; (链表实际长度)

#include<iostream>
using std::cout;
using std::cin;
using std::endl;

// 定义节点数据类型（可根据需要修改）
typedef int Type;

class List1 {
private:
    Type* L;        // 动态数组，存储链表节点
    int size;       // 链表限定长度（容量）
    int Length;     // 链表实际长度

public:
    // 构造函数
    List1(int s = 100) {
        size = s;
        Length = 0;
        L = new Type[size];
    }
    
    // 拷贝构造函数
    List1(const List1& ob) {
        size = ob.size;
        Length = ob.Length;
        L = new Type[size];
        for(int i = 0; i < Length; i++) {
            L[i] = ob.L[i];
        }
    }
    
    // 析构函数
    ~List1() {
        delete[] L;
    }
    
    // 赋值运算符重载
    List1& operator=(const List1& ob) {
        if(this != &ob) {
            delete[] L;
            size = ob.size;
            Length = ob.Length;
            L = new Type[size];
            for(int i = 0; i < Length; i++) {
                L[i] = ob.L[i];
            }
        }
        cout << "List1赋值运算符被调用" << endl;
        return *this;
    }
    
    // 在链表尾部插入元素
    bool Append(Type value) {
        if(Length >= size) {
            cout << "链表已满，无法插入元素" << endl;
            return false;
        }
        L[Length] = value;
        Length++;
        cout << "插入元素 " << value << " 到链表尾部" << endl;
        return true;
    }
    
    // 在指定位置插入元素
    bool Insert(int pos, Type value) {
        if(pos < 0 || pos > Length) {
            cout << "插入位置无效" << endl;
            return false;
        }
        if(Length >= size) {
            cout << "链表已满，无法插入元素" << endl;
            return false;
        }
        for(int i = Length; i > pos; i--) {
            L[i] = L[i-1];
        }
        L[pos] = value;
        Length++;
        cout << "在位置 " << pos << " 插入元素 " << value << endl;
        return true;
    }
    
    // 删除指定位置的元素
    bool Remove(int pos) {
        if(pos < 0 || pos >= Length) {
            cout << "删除位置无效" << endl;
            return false;
        }
        Type value = L[pos];
        for(int i = pos; i < Length - 1; i++) {
            L[i] = L[i+1];
        }
        Length--;
        cout << "删除位置 " << pos << " 的元素 " << value << endl;
        return true;
    }
    
    // 获取指定位置的元素
    bool Get(int pos, Type& value) const {
        if(pos < 0 || pos >= Length) {
            cout << "位置无效" << endl;
            return false;
        }
        value = L[pos];
        return true;
    }
    
    // 修改指定位置的元素
    bool Set(int pos, Type value) {
        if(pos < 0 || pos >= Length) {
            cout << "位置无效" << endl;
            return false;
        }
        L[pos] = value;
        cout << "将位置 " << pos << " 的元素修改为 " << value << endl;
        return true;
    }
    
    // 查找元素，返回第一次出现的位置
    int Find(Type value) const {
        for(int i = 0; i < Length; i++) {
            if(L[i] == value) {
                return i;
            }
        }
        return -1;
    }
    
    // 获取链表长度
    int GetLength() const {
        return Length;
    }
    
    // 获取链表容量
    int GetSize() const {
        return size;
    }
    
    // 判断链表是否为空
    bool IsEmpty() const {
        return Length == 0;
    }
    
    // 判断链表是否已满
    bool IsFull() const {
        return Length >= size;
    }
    
    // 清空链表
    void Clear() {
        Length = 0;
        cout << "链表已清空" << endl;
    }
    
    // 显示链表所有元素
    void Display() const {
        if(Length == 0) {
            cout << "链表为空" << endl;
            return;
        }
        cout << "链表元素: [";
        for(int i = 0; i < Length; i++) {
            cout << L[i];
            if(i < Length - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
        cout << "实际长度: " << Length << ", 容量: " << size << endl;
    }
    
    // 显示链表结构（带索引）
    void DisplayStructure() const {
        cout << "\n链表结构:" << endl;
        cout << "索引: ";
        for(int i = 0; i < size; i++) {
            cout << "[" << i << "]";
            if(i < size - 1) cout << " ";
        }
        cout << endl;
        cout << "数据: ";
        for(int i = 0; i < size; i++) {
            if(i < Length) {
                cout << " " << L[i] << " ";
            } else {
                cout << " - ";
            }
            if(i < size - 1) cout << " ";
        }
        cout << endl;
        cout << "状态: ";
        for(int i = 0; i < size; i++) {
            if(i < Length) {
                cout << " 实 ";
            } else {
                cout << " 空 ";
            }
            if(i < size - 1) cout << " ";
        }
        cout << endl;
        cout << "实际长度: " << Length << ", 容量: " << size << endl;
    }
};

int main() {
    cout << "测试List1类（基于数组的链表）" << endl;
    cout << endl;
    
    // 测试构造函数
    cout << "1. 构造函数测试:" << endl;
    List1 list1(10);
    list1.Display();
    
    // 测试Append函数
    cout << "\n2. Append函数测试:" << endl;
    list1.Append(10);
    list1.Append(20);
    list1.Append(30);
    list1.Append(40);
    list1.Display();
    
    // 测试Insert函数
    cout << "\n3. Insert函数测试:" << endl;
    list1.Insert(0, 5);
    list1.Insert(3, 25);
    list1.Insert(6, 50);
    list1.Display();
    
    // 测试Remove函数
    cout << "\n4. Remove函数测试:" << endl;
    list1.Remove(0);
    list1.Remove(3);
    list1.Remove(4);
    list1.Display();
    
    // 测试Get和Set函数
    cout << "\n5. Get和Set函数测试:" << endl;
    Type value;
    list1.Get(2, value);
    cout << "位置2的元素是: " << value << endl;
    list1.Set(2, 100);
    list1.Display();
    
    // 测试Find函数
    cout << "\n6. Find函数测试:" << endl;
    cout << "查找元素30: 位置 " << list1.Find(30) << endl;
    cout << "查找元素100: 位置 " << list1.Find(100) << endl;
    cout << "查找元素999: 位置 " << list1.Find(999) << endl;
    
    // 测试拷贝构造函数
    cout << "\n7. 拷贝构造函数测试:" << endl;
    List1 list2 = list1;
    list2.Display();
    
    // 测试赋值运算符
    cout << "\n8. 赋值运算符测试:" << endl;
    List1 list3;
    list3 = list1;
    list3.Display();
    
    // 测试Clear函数
    cout << "\n9. Clear函数测试:" << endl;
    list1.Clear();
    list1.Display();
    
    // 测试边界情况
    cout << "\n10. 边界情况测试:" << endl;
    List1 list4(5);
    for(int i = 1; i <= 6; i++) {
        cout << "尝试插入 " << i * 10 << ": ";
        list4.Append(i * 10);
    }
    list4.Display();
    
    // 测试插入无效位置
    cout << "\n尝试在无效位置插入:" << endl;
    list4.Insert(10, 99);
    list4.Insert(-1, 99);
    
    // 测试删除无效位置
    cout << "\n尝试删除无效位置:" << endl;
    list4.Remove(10);
    list4.Remove(-1);
    
    // 显示详细结构
    cout << "\n11. 显示详细链表结构:" << endl;
    list4.DisplayStructure();
    
    // 测试IsEmpty和IsFull
    cout << "\n12. 状态测试:" << endl;
    List1 list5;
    cout << "list5是否为空: " << (list5.IsEmpty() ? "是" : "否") << endl;
    cout << "list5是否已满: " << (list5.IsFull() ? "是" : "否") << endl;
    
    List1 list6(3);
    list6.Append(1);
    list6.Append(2);
    list6.Append(3);
    cout << "list6是否为空: " << (list6.IsEmpty() ? "是" : "否") << endl;
    cout << "list6是否已满: " << (list6.IsFull() ? "是" : "否") << endl;
    
    cout << "\n程序结束，观察析构函数调用顺序" << endl;
    
    return 0;
}