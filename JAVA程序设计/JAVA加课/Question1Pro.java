/**
 * 定义一个接口 Shape，表示几何形状。
 * 任何实现该接口的类都必须定义 `area()` 方法来计算面积。
 */
interface Shape {
    /**
     * 计算形状的面积。
     * @return 面积的值
     */
    double area();
}

/**
 * 三角形类，实现 Shape 接口。
 * 使用三边长计算三角形面积（海伦公式）。
 */
class Triangle implements Shape {
    double a, b, c; // 三角形的三条边长

    /**
     * 构造方法，初始化三角形的三条边长。
     * @param a 边长 a
     * @param b 边长 b
     * @param c 边长 c
     */
    public Triangle(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    /**
     * 使用海伦公式计算三角形面积。
     * @return 三角形的面积
     */
    @Override
    public double area() {
        double p = (this.a + this.b + this.c) / 2; // 计算半周长
        return Math.sqrt(p * (p - this.a) * (p - this.b) * (p - this.c)); // 面积公式
    }
}

/**
 * 圆形类，实现 Shape 接口。
 * 使用半径计算圆的面积。
 */
class Circle implements Shape {
    double r; // 圆的半径

    /**
     * 构造方法，初始化圆的半径。
     * @param r 圆的半径
     */
    public Circle(double r) {
        this.r = r;
    }

    /**
     * 使用公式 π*r^2 计算圆的面积。
     * @return 圆的面积
     */
    @Override
    public double area() {
        return Math.PI * r * r; // πr^2
    }
}

/**
 * 矩形类，实现 Shape 接口。
 * 使用高和宽计算矩形面积。
 */
class Rectangle implements Shape {
    double h, w; // 矩形的高和宽

    /**
     * 构造方法，初始化矩形的高和宽。
     * @param h 高度
     * @param w 宽度
     */
    public Rectangle(double h, double w) {
        this.h = h;
        this.w = w;
    }

    /**
     * 使用公式 h*w 计算矩形的面积。
     * @return 矩形的面积
     */
    @Override
    public double area() {
        return this.h * this.w; // 高 * 宽
    }
}

/**
 * 主类，用于测试 Shape 接口及其实现类。
 */
public class Question1Pro {
    public static void main(String[] args) {
        // 定义一个 Shape 类型的数组，存储不同的形状
        Shape[] shapes = new Shape[3];
        
        // 创建不同形状的对象并存入数组
        shapes[0] = new Triangle(1, 2, 2.213); // 创建一个三角形
        shapes[1] = new Circle(2); // 创建一个半径为 2 的圆
        shapes[2] = new Rectangle(10, 20); // 创建一个 10x20 的矩形

        // 遍历数组，计算并打印每个形状的面积
        for (Shape s : shapes) {
            System.out.println(s.area()); // 调用 area 方法计算面积
        }
    }
}