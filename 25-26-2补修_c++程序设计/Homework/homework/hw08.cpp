// assignment
// 将Vector类推广到n维空间上，即矢量对象Ob(x0,x1,x2,......,xn-1)，该如何实现以上功能？

#include<bits/stdc++.h>
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::sqrt;

// n维矢量类
class Vector {
private:
    int* components;  // 动态数组存储各分量
    int dimension;    // 维度

public:
    // 构造函数：初始化n维矢量
    Vector(int dim = 2) {
        dimension = dim;
        components = new int[dimension];
        for(int i = 0; i < dimension; i++) {
            components[i] = 0;
        }
    }
    
    // 带参数构造函数：使用数组初始化
    Vector(int dim, int* arr) {
        dimension = dim;
        components = new int[dimension];
        for(int i = 0; i < dimension; i++) {
            components[i] = arr[i];
        }
    }
    
    // 拷贝构造函数
    Vector(const Vector& v) {
        dimension = v.dimension;
        components = new int[dimension];
        for(int i = 0; i < dimension; i++) {
            components[i] = v.components[i];
        }
    }
    
    // 析构函数
    ~Vector() {
        delete[] components;
    }
    
    // 赋值运算符重载
    Vector& operator=(const Vector& v) {
        if(this != &v) {
            delete[] components;
            dimension = v.dimension;
            components = new int[dimension];
            for(int i = 0; i < dimension; i++) {
                components[i] = v.components[i];
            }
        }
        return *this;
    }
    
    // 输出数据成员
    void display() {
        cout << "(";
        for(int i = 0; i < dimension; i++) {
            cout << components[i];
            if(i < dimension - 1) cout << ", ";
        }
        cout << ")" << endl;
    }
    
    // 类外访问数据成员函数
    int getComponent(int index) const {
        if(index >= 0 && index < dimension) {
            return components[index];
        }
        return 0;
    }
    
    int getDimension() const {
        return dimension;
    }
    
    // 设置分量
    void setComponent(int index, int value) {
        if(index >= 0 && index < dimension) {
            components[index] = value;
        }
    }
    
    // 矢量加法
    Vector Add(const Vector& ob2) const {
        if(dimension != ob2.dimension) {
            cout << "错误：矢量维度不同，无法相加！" << endl;
            return Vector(dimension);
        }
        
        Vector result(dimension);
        for(int i = 0; i < dimension; i++) {
            result.components[i] = components[i] + ob2.components[i];
        }
        return result;
    }
    
    // 矢量减法
    Vector Sub(const Vector& ob2) const {
        if(dimension != ob2.dimension) {
            cout << "错误：矢量维度不同，无法相减！" << endl;
            return Vector(dimension);
        }
        
        Vector result(dimension);
        for(int i = 0; i < dimension; i++) {
            result.components[i] = components[i] - ob2.components[i];
        }
        return result;
    }
    
    // 矢量点乘（内积）
    int DotProduct(const Vector& ob2) const {
        if(dimension != ob2.dimension) {
            cout << "错误：矢量维度不同，无法点乘！" << endl;
            return 0;
        }
        
        int result = 0;
        for(int i = 0; i < dimension; i++) {
            result += components[i] * ob2.components[i];
        }
        return result;
    }
    
    // 标量乘法
    Vector ScalarMultiply(int scalar) const {
        Vector result(dimension);
        for(int i = 0; i < dimension; i++) {
            result.components[i] = components[i] * scalar;
        }
        return result;
    }
    
    // 计算模长
    double Magnitude() const {
        int sum = 0;
        for(int i = 0; i < dimension; i++) {
            sum += components[i] * components[i];
        }
        return sqrt(sum);
    }
};

// 矩阵类（n×m矩阵）
class Matrix {
private:
    int** data;     // 二维动态数组
    int rows;       // 行数
    int cols;       // 列数

public:
    // 构造函数
    Matrix(int r = 2, int c = 2) {
        rows = r;
        cols = c;
        data = new int*[rows];
        for(int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for(int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
        }
    }
    
    // 带参数构造函数
    Matrix(int r, int c, int** arr) {
        rows = r;
        cols = c;
        data = new int*[rows];
        for(int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for(int j = 0; j < cols; j++) {
                data[i][j] = arr[i][j];
            }
        }
    }
    
    // 拷贝构造函数
    Matrix(const Matrix& m) {
        rows = m.rows;
        cols = m.cols;
        data = new int*[rows];
        for(int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for(int j = 0; j < cols; j++) {
                data[i][j] = m.data[i][j];
            }
        }
    }
    
    // 析构函数
    ~Matrix() {
        for(int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }
    
    // 输出矩阵
    void display() {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                cout << setw(5) << data[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    // 获取矩阵中的行向量
    Vector getRowVector(int row) const {
        if(row >= 0 && row < rows) {
            Vector v(cols);
            for(int j = 0; j < cols; j++) {
                v.setComponent(j, data[row][j]);
            }
            return v;
        }
        return Vector(cols);
    }
    
    // 获取矩阵中的列向量
    Vector getColVector(int col) const {
        if(col >= 0 && col < cols) {
            Vector v(rows);
            for(int i = 0; i < rows; i++) {
                v.setComponent(i, data[i][col]);
            }
            return v;
        }
        return Vector(rows);
    }
    
    // 设置矩阵元素
    void setElement(int i, int j, int value) {
        if(i >= 0 && i < rows && j >= 0 && j < cols) {
            data[i][j] = value;
        }
    }
    
    // 矩阵加法
    Matrix Add(const Matrix& ob2) const {
        if(rows != ob2.rows || cols != ob2.cols) {
            cout << "错误：矩阵维度不匹配，无法相加！" << endl;
            return Matrix(rows, cols);
        }
        
        Matrix result(rows, cols);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + ob2.data[i][j];
            }
        }
        return result;
    }
    
    // 矩阵减法
    Matrix Sub(const Matrix& ob2) const {
        if(rows != ob2.rows || cols != ob2.cols) {
            cout << "错误：矩阵维度不匹配，无法相减！" << endl;
            return Matrix(rows, cols);
        }
        
        Matrix result(rows, cols);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - ob2.data[i][j];
            }
        }
        return result;
    }
    
    // 矩阵乘法
    Matrix Mult(const Matrix& ob2) const {
        if(cols != ob2.rows) {
            cout << "错误：矩阵维度不匹配，无法相乘！" << endl;
            return Matrix(rows, ob2.cols);
        }
        
        Matrix result(rows, ob2.cols);
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < ob2.cols; j++) {
                result.data[i][j] = 0;
                for(int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * ob2.data[k][j];
                }
            }
        }
        return result;
    }
};

int main() {
    cout << "========== n维矢量测试 ==========" << endl;
    
    // 创建3维矢量
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    
    Vector v1(3, arr1);
    Vector v2(3, arr2);
    
    cout << "矢量v1: ";
    v1.display();
    cout << "矢量v2: ";
    v2.display();
    
    // 矢量加法
    Vector v3 = v1.Add(v2);
    cout << "v1 + v2 = ";
    v3.display();
    
    // 矢量减法
    Vector v4 = v1.Sub(v2);
    cout << "v1 - v2 = ";
    v4.display();
    
    // 点乘
    int dot = v1.DotProduct(v2);
    cout << "v1 · v2 = " << dot << endl;
    
    // 标量乘法
    Vector v5 = v1.ScalarMultiply(3);
    cout << "3 × v1 = ";
    v5.display();
    
    // 模长
    cout << "|v1| = " << v1.Magnitude() << endl;
    
    cout << "\n========== 矩阵测试 ==========" << endl;
    
    // 创建2×3矩阵
    Matrix m1(2, 3);
    m1.setElement(0, 0, 1);
    m1.setElement(0, 1, 2);
    m1.setElement(0, 2, 3);
    m1.setElement(1, 0, 4);
    m1.setElement(1, 1, 5);
    m1.setElement(1, 2, 6);
    
    cout << "矩阵m1:" << endl;
    m1.display();
    
    // 获取行向量
    Vector row0 = m1.getRowVector(0);
    cout << "第0行向量: ";
    row0.display();
    
    // 获取列向量
    Vector col1 = m1.getColVector(1);
    cout << "第1列向量: ";
    col1.display();
    
    return 0;
}