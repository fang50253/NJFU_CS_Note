// assignment
// 定义一个链表类List2，其结构中私有数据成员如下表：
// 1.类外的链表数组 Type tmp[Length];
// 2.tmp[0], tmp[1], tmp[2], ..., tmp[Length-1] (链尾节点)

#include<iostream>
using std::cout;
using std::cin;
using std::endl;

// 定义节点数据类型（可根据需要修改）
typedef int Type;

class List2 {
private:
    Type* tmp;      // 指向类外链表数组的指针
    int Length;     // 链表实际长度

public:
    // 构造函数
    List2() {
        tmp = nullptr;
        Length = 0;
    }
    
    // 带参数构造函数（使用外部数组）
    List2(Type arr[], int len) {
        Length = len;
        tmp = new Type[Length];
        for(int i = 0; i < Length; i++) {
            tmp[i] = arr[i];
        }
    }
    
    // 拷贝构造函数
    List2(const List2& ob) {
        Length = ob.Length;
        tmp = new Type[Length];
        for(int i = 0; i < Length; i++) {
            tmp[i] = ob.tmp[i];
        }
    }
    
    // 析构函数
    ~List2() {
        delete[] tmp;
    }
    
    // 赋值运算符重载
    List2& operator=(const List2& ob) {
        if(this != &ob) {
            delete[] tmp;
            Length = ob.Length;
            tmp = new Type[Length];
            for(int i = 0; i < Length; i++) {
                tmp[i] = ob.tmp[i];
            }
        }
        cout << "List2赋值运算符被调用" << endl;
        return *this;
    }
    
    // 关联外部数组
    void Attach(Type arr[], int len) {
        delete[] tmp;
        Length = len;
        tmp = new Type[Length];
        for(int i = 0; i < Length; i++) {
            tmp[i] = arr[i];
        }
        cout << "已关联外部数组，长度: " << Length << endl;
    }
    
    // 在链表尾部添加元素
    bool Append(Type value) {
        Type* newTmp = new Type[Length + 1];
        for(int i = 0; i < Length; i++) {
            newTmp[i] = tmp[i];
        }
        newTmp[Length] = value;
        delete[] tmp;
        tmp = newTmp;
        Length++;
        cout << "在尾部添加元素 " << value << "，新长度: " << Length << endl;
        return true;
    }
    
    // 在指定位置插入元素
    bool Insert(int pos, Type value) {
        if(pos < 0 || pos > Length) {
            cout << "插入位置无效" << endl;
            return false;
        }
        Type* newTmp = new Type[Length + 1];
        for(int i = 0; i < pos; i++) {
            newTmp[i] = tmp[i];
        }
        newTmp[pos] = value;
        for(int i = pos; i < Length; i++) {
            newTmp[i + 1] = tmp[i];
        }
        delete[] tmp;
        tmp = newTmp;
        Length++;
        cout << "在位置 " << pos << " 插入元素 " << value << "，新长度: " << Length << endl;
        return true;
    }
    
    // 删除指定位置的元素
    bool Remove(int pos) {
        if(pos < 0 || pos >= Length) {
            cout << "删除位置无效" << endl;
            return false;
        }
        Type value = tmp[pos];
        Type* newTmp = new Type[Length - 1];
        for(int i = 0; i < pos; i++) {
            newTmp[i] = tmp[i];
        }
        for(int i = pos + 1; i < Length; i++) {
            newTmp[i - 1] = tmp[i];
        }
        delete[] tmp;
        tmp = newTmp;
        Length--;
        cout << "删除位置 " << pos << " 的元素 " << value << "，新长度: " << Length << endl;
        return true;
    }
    
    // 获取指定位置的元素
    bool Get(int pos, Type& value) const {
        if(pos < 0 || pos >= Length) {
            cout << "位置无效" << endl;
            return false;
        }
        value = tmp[pos];
        return true;
    }
    
    // 修改指定位置的元素
    bool Set(int pos, Type value) {
        if(pos < 0 || pos >= Length) {
            cout << "位置无效" << endl;
            return false;
        }
        tmp[pos] = value;
        cout << "将位置 " << pos << " 的元素修改为 " << value << endl;
        return true;
    }
    
    // 查找元素，返回第一次出现的位置
    int Find(Type value) const {
        for(int i = 0; i < Length; i++) {
            if(tmp[i] == value) {
                return i;
            }
        }
        return -1;
    }
    
    // 获取链表长度
    int GetLength() const {
        return Length;
    }
    
    // 判断链表是否为空
    bool IsEmpty() const {
        return Length == 0;
    }
    
    // 清空链表
    void Clear() {
        delete[] tmp;
        tmp = nullptr;
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
            cout << tmp[i];
            if(i < Length - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
        cout << "链表长度: " << Length << endl;
    }
    
    // 显示链表详细信息
    void DisplayDetail() const {
        cout << "\n链表详细信息:" << endl;
        cout << "实际长度: " << Length << endl;
        if(Length > 0) {
            cout << "数组元素: ";
            for(int i = 0; i < Length; i++) {
                cout << "tmp[" << i << "] = " << tmp[i];
                if(i < Length - 1) cout << ", ";
            }
            cout << endl;
        }
    }
    
    // 获取外部数组指针（用于类外访问）
    Type* GetArray() const {
        return tmp;
    }
};

int main() {
    cout << "测试List2类（使用外部数组的链表）" << endl;
    cout << endl;
    
    // 测试构造函数
    cout << "1. 默认构造函数测试:" << endl;
    List2 list1;
    list1.Display();
    
    // 测试带参数构造函数
    cout << "\n2. 带参数构造函数测试:" << endl;
    int arr1[] = {10, 20, 30, 40, 50};
    List2 list2(arr1, 5);
    list2.Display();
    
    // 测试Append函数
    cout << "\n3. Append函数测试:" << endl;
    List2 list3;
    list3.Append(10);
    list3.Append(20);
    list3.Append(30);
    list3.Append(40);
    list3.Display();
    
    // 测试Insert函数
    cout << "\n4. Insert函数测试:" << endl;
    List2 list4;
    list4.Append(10);
    list4.Append(20);
    list4.Append(30);
    list4.Display();
    list4.Insert(0, 5);
    list4.Insert(2, 15);
    list4.Insert(5, 35);
    list4.Display();
    
    // 测试Remove函数
    cout << "\n5. Remove函数测试:" << endl;
    List2 list5;
    for(int i = 1; i <= 10; i++) {
        list5.Append(i * 10);
    }
    list5.Display();
    list5.Remove(0);
    list5.Remove(4);
    list5.Remove(7);
    list5.Display();
    
    // 测试Get和Set函数
    cout << "\n6. Get和Set函数测试:" << endl;
    List2 list6;
    for(int i = 1; i <= 5; i++) {
        list6.Append(i * 10);
    }
    list6.Display();
    Type value;
    list6.Get(2, value);
    cout << "位置2的元素是: " << value << endl;
    list6.Set(2, 100);
    list6.Display();
    
    // 测试Find函数
    cout << "\n7. Find函数测试:" << endl;
    List2 list7;
    for(int i = 1; i <= 8; i++) {
        list7.Append(i * 5);
    }
    list7.Display();
    cout << "查找元素20: 位置 " << list7.Find(20) << endl;
    cout << "查找元素40: 位置 " << list7.Find(40) << endl;
    cout << "查找元素100: 位置 " << list7.Find(100) << endl;
    
    // 测试拷贝构造函数
    cout << "\n8. 拷贝构造函数测试:" << endl;
    List2 list8;
    for(int i = 1; i <= 3; i++) {
        list8.Append(i * 100);
    }
    list8.Display();
    List2 list9 = list8;
    list9.Display();
    
    // 测试赋值运算符
    cout << "\n9. 赋值运算符测试:" << endl;
    List2 list10;
    list10 = list8;
    list10.Display();
    
    // 测试Attach函数
    cout << "\n10. Attach函数测试:" << endl;
    int arr2[] = {1, 2, 3, 4, 5, 6};
    List2 list11;
    list11.Attach(arr2, 6);
    list11.Display();
    
    // 测试Clear函数
    cout << "\n11. Clear函数测试:" << endl;
    List2 list12;
    for(int i = 1; i <= 5; i++) {
        list12.Append(i);
    }
    cout << "清空前: ";
    list12.Display();
    list12.Clear();
    cout << "清空后: ";
    list12.Display();
    
    // 测试IsEmpty
    cout << "\n12. IsEmpty函数测试:" << endl;
    List2 list13;
    cout << "list13是否为空: " << (list13.IsEmpty() ? "是" : "否") << endl;
    list13.Append(100);
    cout << "list13是否为空: " << (list13.IsEmpty() ? "是" : "否") << endl;
    
    // 测试边界情况
    cout << "\n13. 边界情况测试:" << endl;
    List2 list14;
    cout << "尝试在空链表删除元素:" << endl;
    list14.Remove(0);
    cout << "\n尝试在无效位置插入:" << endl;
    list14.Insert(-1, 99);
    list14.Insert(10, 99);
    cout << "\n尝试获取无效位置元素:" << endl;
    Type val;
    list14.Get(0, val);
    
    // 显示详细信息
    cout << "\n14. 显示详细信息测试:" << endl;
    List2 list15;
    for(int i = 0; i < 6; i++) {
        list15.Append((i + 1) * 10);
    }
    list15.DisplayDetail();
    
    // 测试GetArray函数
    cout << "\n15. GetArray函数测试:" << endl;
    Type* arr = list15.GetArray();
    cout << "通过GetArray获取的数组: ";
    for(int i = 0; i < list15.GetLength(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    cout << "\n程序结束，观察析构函数调用顺序" << endl;
    
    return 0;
}