interface Shape{
    double area();
}
class Triangle implements Shape{
    double a,b,c;
    public Triangle(double a,double b,double c){
        this.a=a;
        this.b=b;
        this.c=c;
    }
    @Override
    public double area(){
        double p=(this.a+this.b+this.c)/2;
        return Math.sqrt(p*(p-this.a)*(p-this.b)*(p-this.c));
    }
}
class Circle implements Shape{
    double r;
    public Circle(double r){
        this.r=r;
    }
    @Override
    public double area(){
        return Math.PI*r*r;
    }
}
class Rectangle implements Shape{
    double h,w;
    public Rectangle(double h,double w){
        this.h=h;
        this.w=w;
    }
    @Override
    public double area(){
        return this.h*this.w;
    }
}
public class Question1{
    public static void main(String[] args){
        Shape[] shapes=new Shape[3];
        shapes[0]=new Triangle(1,2,2.213);
        shapes[1]=new Circle(2);
        shapes[2]=new Rectangle(10,20);
        for(Shape s:shapes){
            System.out.println(s.area());
        }
    }
}