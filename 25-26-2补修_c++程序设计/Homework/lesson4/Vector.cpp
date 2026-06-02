#include<bits/stdc++.h>
using namespace std;
class Vector{
    private:
    int x,y;
    public:
    void display(){
        cout<<"x = "<<x<<" y = "<<y<<endl;
    }
    int getx(){
        return x;
    }
    int gety(){
        return y;
    }
    Vector Add(const Vector &ob2){
        Vector ob3;
        ob3.x = x + ob2.x;
        ob3.y = y + ob2.y;
        return ob3;
    }
    Vector Sub(const Vector &ob2){
        Vector ob3;
        ob3.x = x - ob2.x;
        ob3.y = y - ob2.y;
        return ob3;
    }
    int Mult(const Vector &ob2){
        return x * ob2.x + y * ob2.y;
    }
    Vector(int x,int y){
        this->x = x;
        this->y = y;
    }
    Vector(){
        x = 0;
        y = 0;
    }
};
class Matrix{
    private:
    int lefttop,rightbottom;
    int righttop,leftbottom;
    public:
    void display(){
        cout<<"lefttop = "<<lefttop<<" rightbottom = "<<rightbottom<<" righttop = "<<righttop<<" leftbottom = "<<leftbottom<<endl;
    }
    Vector getVector(int i,int j){
        if(i == j){
            return Vector(lefttop,rightbottom);
        }
        else{
            return Vector(righttop,leftbottom);
        }
    }
    Matrix Add(const Matrix &ob2){
        Matrix ob3;
        ob3.lefttop = lefttop + ob2.lefttop;
        ob3.rightbottom = rightbottom + ob2.rightbottom;
        ob3.righttop = righttop + ob2.righttop;
        ob3.leftbottom = leftbottom + ob2.leftbottom;
        return ob3;
    }
    Matrix Sub(const Matrix &ob2){
        Matrix ob3;
        ob3.lefttop = lefttop - ob2.lefttop;
        ob3.rightbottom = rightbottom - ob2.rightbottom;
        ob3.righttop = righttop - ob2.righttop;
        ob3.leftbottom = leftbottom - ob2.leftbottom;
        return ob3;
    }
    Matrix Mult(const Matrix &ob2){
        Matrix ob3;
        ob3.lefttop = lefttop * ob2.lefttop + righttop * ob2.leftbottom;
        ob3.rightbottom = rightbottom * ob2.rightbottom + leftbottom * ob2.righttop;
        ob3.righttop = righttop * ob2.righttop + lefttop * ob2.rightbottom;
        ob3.leftbottom = leftbottom * ob2.leftbottom + rightbottom * ob2.lefttop;
        return ob3;
    }
    Matrix(int lefttop,int rightbottom,int righttop,int leftbottom){
        this->lefttop = lefttop;
        this->rightbottom = rightbottom;
        this->righttop = righttop;
        this->leftbottom = leftbottom;
    }
    Matrix(){
        lefttop = 0;
        rightbottom = 0;
        righttop = 0;
        leftbottom = 0;
    }
};
int main(){
    Vector ob1(1,2),ob2(3,4);
    ob1.display();
    Vector ob3 = ob1.Add(ob2);
    ob3.display();
    ob3 = ob1.Sub(ob2);
    ob3.display();
    Matrix ob4(1,2,3,4),ob5(5,6,7,8);
    ob4.display();
    Matrix ob6 = ob4.Add(ob5);
    ob6.display();
    ob6 = ob4.Sub(ob5);
    ob6.display();
    ob6 = ob4.Mult(ob5);
    ob6.display();
    return 0;
}