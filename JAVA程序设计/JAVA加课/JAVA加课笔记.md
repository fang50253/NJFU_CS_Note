# 题型
* 选择20 
* 填空10
* 程序阅读(每一个空格都是填一行）10
* 代码完形填空 10
* 编程题 50


# 关于编程题
## 输入输出
* 输出
```java
System.out.println()
```
* 输入函数
```java
System.in
```
* 用缓冲区读
```java
import java.util.*;
new Scanner(System.in)
```
* 生成伪随机数
```java
Random//按照从多少到多少到随机数
```
以下是ChatGPT生成的样例：
```java
import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Random random = new Random();
        int min = 10; // 下限
        int max = 20; // 上限（不包含）
        int randomNumber = random.nextInt(max - min) + min;
        System.out.println("随机整数: " + randomNumber);
    }
}
```
* 字符串类(String类)
```java
String.split(正则表达式)
```
以下是由ChatGPT生成的样例

基本用法：
```java
public class Main {
    public static void main(String[] args) {
        String str = "apple,orange,banana";
        String[] result = str.split(",");
        for (String s : result) {
            System.out.println(s);
        }
    }
}
```
输出结果
```
apple
orange
banana
```
正则表达式
```java
public class Main {
    public static void main(String[] args) {
        String str = "apple123orange456banana";
        String[] result = str.split("\\d+"); // 按数字拆分
        for (String s : result) {
            System.out.println(s);
        }
    }
}
```
使用limit参数
```java
public class Main {
    public static void main(String[] args) {
        String str = "apple,orange,banana,grape";

        // 限制分割成最多 2 个元素
        String[] result1 = str.split(",", 2);
        for (String s : result1) {
            System.out.println(s);
        }

        // 不限制分割的元素数量（默认）
        String[] result2 = str.split(",", 0);
        for (String s : result2) {
            System.out.println(s);
        }
    }
}
```
统计每个单词出现的频率，最为理想的数据结构：哈希表

实例化HashMap

包装器类Integer





# 懂得都懂系列
## 写方法
* 写一个方法判断一个数是否是素数

* 写一个方法判断一个数字是否是回文数
* 写一个方法判断一个数字是否是完数
* 写一个方法判断一个数字是否是水仙花数(以前没考过，应该不会考)
* 可能会出现从键盘上输入一个数字
```
public class NumberUtils {

    // 判断一个数是否是素数
    public static boolean isPrime(int num) {
        if (num <= 1) {
            return false;
        }
        for (int i = 2; i <= Math.sqrt(num); i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    // 判断一个数字是否是回文数
    public static boolean isPalindrome(int num) {
        int original = num;
        int reversed = 0;
        while (num != 0) {
            int digit = num % 10;
            reversed = reversed * 10 + digit;
            num /= 10;
        }
        return original == reversed;
    }

    // 判断一个数字是否是完数
    public static boolean isPerfectNumber(int num) {
        if (num <= 1) {
            return false;
        }
        int sum = 0;
        for (int i = 1; i <= num / 2; i++) {
            if (num % i == 0) {
                sum += i;
            }
        }
        return sum == num;
    }

    // 判断一个数字是否是水仙花数
    public static boolean isArmstrong(int num) {
        int original = num;
        int sum = 0;
        int digits = (int) Math.log10(num) + 1; // 计算数字的位数
        while (num != 0) {
            int digit = num % 10;
            sum += Math.pow(digit, digits);
            num /= 10;
        }
        return original == sum;
    }

    public static void main(String[] args) {
        // 示例测试
        System.out.println(isPrime(7)); // true
        System.out.println(isPalindrome(121)); // true
        System.out.println(isPerfectNumber(28)); // true
        System.out.println(isArmstrong(153)); // true
    }
}
```
## 第二章

教材P63 2-15   输入一个班的成绩写入到一维数组中，求最高分、平均分，并统计各分数段的人数，其中的分数段有：不及格(<60)、及格(60~69)、中(70~79)、良(80~89)、优(>90)。PS：可能不考成绩，是分出某一个产品的销售额
```java
import java.util.Scanner;
public class ScoreStatistics {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        // 输入班级人数
        System.out.print("请输入班级人数: ");
        int n = scanner.nextInt();
        int[] scores = new int[n];
        // 输入成绩
        System.out.println("请输入 " + n + " 个学生的成绩:");
        for (int i = 0; i < n; i++) {
            scores[i] = scanner.nextInt();
        }
        // 初始化统计变量
        int maxScore = Integer.MIN_VALUE;
        int totalScore = 0;
        int failCount = 0, passCount = 0, middleCount = 0, goodCount = 0, excellentCount = 0;
        // 遍历数组，统计最高分、总分和各分数段人数
        for (int score : scores) {
            // 最高分
            if (score > maxScore) {
                maxScore = score;
            }
            // 总分
            totalScore += score;

            // 分数段统计
            if (score < 60) {
                failCount++;
            } else if (score <= 69) {
                passCount++;
            } else if (score <= 79) {
                middleCount++;
            } else if (score <= 89) {
                goodCount++;
            } else {
                excellentCount++;
            }
        }
        // 计算平均分
        double averageScore = totalScore / (double) n;
        // 输出结果
        System.out.println("\n统计结果:");
        System.out.printf("最高分: %d\n", maxScore);
        System.out.printf("平均分: %.2f\n", averageScore);
        System.out.println("分数段统计:");
        System.out.printf("不及格 (<60): %d 人\n", failCount);
        System.out.printf("及格 (60~69): %d 人\n", passCount);
        System.out.printf("中等 (70~79): %d 人\n", middleCount);
        System.out.printf("良好 (80~89): %d 人\n", goodCount);
        System.out.printf("优秀 (>90): %d 人\n", excellentCount);
        scanner.close();
    }
}
```
教材P63 2-19   设有一条绳子，长2000m，每天减去1/3，计算多少天后长度变为1cm。会改数字
```java
public class RopeLengthReduction {
    public static void main(String[] args) {
        // 初始化绳子的初始长度 (以厘米为单位)
        double length = 2000 * 100; // 2000 米 = 200000 厘米
        int days = 0;

        // 每天减少 1/3 的长度，直到长度小于等于 1cm
        while (length > 1) {
            length -= length / 3; // 减少 1/3
            days++; // 记录天数
        }

        // 输出所需的天数
        System.out.println("绳子的长度变为 1cm 所需的天数: " + days);
    }
}
```
## 第三章
教材P79 3-5   考的是员工，不是学生，但是没有区别   并实现当数组满了以后自动扩容
```
编写一个学生类student，包含的属性有学号、姓名、性别、年龄等，将所有学生存储在一个数组中，编写学生管理程序完成如下操作：
1.增加一个学生。2.根据学号删除某个学生。3.将所有学生党年龄增加一岁。4.按数组中顺序显示所有学生党信息。5.将所有的学生按照姓名排序输出。
```
下面代码由ChatGPT生成
```java
import java.util.Scanner;
import java.util.Arrays;

class Student {
    private int id;          // 学号
    private String name;     // 姓名
    private String gender;   // 性别
    private int age;         // 年龄

    // 构造方法
    public Student(int id, String name, String gender, int age) {
        this.id = id;
        this.name = name;
        this.gender = gender;
        this.age = age;
    }

    // 获取学号
    public int getId() {
        return id;
    }

    // 设置年龄
    public void increaseAge() {
        this.age++;
    }

    // 显示学生信息
    public void display() {
        System.out.printf("学号: %d, 姓名: %s, 性别: %s, 年龄: %d\n", id, name, gender, age);
    }

    // 获取姓名 (用于排序)
    public String getName() {
        return name;
    }
}

public class StudentManager {
    private static Student[] students = new Student[100]; // 最大支持100名学生
    private static int studentCount = 0;                  // 当前学生数

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("\n学生管理系统");
            System.out.println("1. 增加一个学生");
            System.out.println("2. 根据学号删除学生");
            System.out.println("3. 将所有学生年龄增加一岁");
            System.out.println("4. 显示所有学生信息");
            System.out.println("5. 按姓名排序显示所有学生");
            System.out.println("0. 退出");
            System.out.print("请选择操作: ");
            int choice = scanner.nextInt();

            switch (choice) {
                case 1 -> addStudent(scanner);
                case 2 -> deleteStudent(scanner);
                case 3 -> increaseAge();
                case 4 -> displayAllStudents();
                case 5 -> sortAndDisplayByName();
                case 0 -> {
                    System.out.println("退出系统！");
                    return;
                }
                default -> System.out.println("无效选择，请重试！");
            }
        }
    }

    // 添加学生
    private static void addStudent(Scanner scanner) {
        if (studentCount >= students.length) {
            System.out.println("学生人数已达上限！");
            return;
        }
        System.out.print("请输入学号: ");
        int id = scanner.nextInt();
        scanner.nextLine(); // 清除换行符
        System.out.print("请输入姓名: ");
        String name = scanner.nextLine();
        System.out.print("请输入性别: ");
        String gender = scanner.nextLine();
        System.out.print("请输入年龄: ");
        int age = scanner.nextInt();

        students[studentCount++] = new Student(id, name, gender, age);
        System.out.println("学生添加成功！");
    }

    // 删除学生
    private static void deleteStudent(Scanner scanner) {
        System.out.print("请输入要删除的学生学号: ");
        int id = scanner.nextInt();
        for (int i = 0; i < studentCount; i++) {
            if (students[i].getId() == id) {
                // 删除操作
                for (int j = i; j < studentCount - 1; j++) {
                    students[j] = students[j + 1];
                }
                students[--studentCount] = null; // 清空最后一个位置
                System.out.println("学生删除成功！");
                return;
            }
        }
        System.out.println("未找到该学号的学生！");
    }

    // 年龄增加一岁
    private static void increaseAge() {
        for (int i = 0; i < studentCount; i++) {
            students[i].increaseAge();
        }
        System.out.println("所有学生年龄增加一岁！");
    }

    // 显示所有学生信息
    private static void displayAllStudents() {
        if (studentCount == 0) {
            System.out.println("当前没有学生！");
            return;
        }
        System.out.println("所有学生信息：");
        for (int i = 0; i < studentCount; i++) {
            students[i].display();
        }
    }

    // 按姓名排序并显示
    private static void sortAndDisplayByName() {
        if (studentCount == 0) {
            System.out.println("当前没有学生！");
            return;
        }
        // 排序
        Arrays.sort(students, 0, studentCount, (s1, s2) -> s1.getName().compareTo(s2.getName()));

        System.out.println("按姓名排序后的学生信息：");
        for (int i = 0; i < studentCount; i++) {
            students[i].display();
        }
    }
}
```
## 第四章
教材P118 4-11编写一个抽象类表示形状，其中有一个求面积的抽象方法，继承该抽象方法分别编写三角形、圆、矩形类，创建一个数组存放创建的各类徒刑对象，输出图形的面积。

以下内容由ChatGPT生成：
```java
// 定义一个抽象类 Shape 表示形状
abstract class Shape {
    // 抽象方法：求面积
    public abstract double getArea();
}

// 三角形类
class Triangle extends Shape {
    private double base;  // 底边
    private double height; // 高

    public Triangle(double base, double height) {
        this.base = base;
        this.height = height;
    }

    @Override
    public double getArea() {
        return 0.5 * base * height; // 面积公式：0.5 * 底 * 高
    }
}

// 圆类
class Circle extends Shape {
    private double radius; // 半径

    public Circle(double radius) {
        this.radius = radius;
    }

    @Override
    public double getArea() {
        return Math.PI * radius * radius; // 面积公式：π * 半径²
    }
}

// 矩形类
class Rectangle extends Shape {
    private double length; // 长
    private double width;  // 宽

    public Rectangle(double length, double width) {
        this.length = length;
        this.width = width;
    }

    @Override
    public double getArea() {
        return length * width; // 面积公式：长 * 宽
    }
}

// 测试类
public class Main {
    public static void main(String[] args) {
        // 创建图形对象数组
        Shape[] shapes = new Shape[3];

        // 创建不同的图形对象并存入数组
        shapes[0] = new Triangle(10, 5);     // 三角形，底边为 10，高为 5
        shapes[1] = new Circle(7);          // 圆，半径为 7
        shapes[2] = new Rectangle(4, 6);    // 矩形，长为 4，宽为 6

        // 遍历数组并输出每个图形的面积
        for (Shape shape : shapes) {
            System.out.println("面积: " + shape.getArea());
        }
    }
}
```
## 第十章 Applet等图形化
哪怕有必要用图形应用接口，起码使用swing，

* 教材 P248 10-7 编写选好程序，在窗体中安排6个标签，每个标签上显示0～9之间的一位数字，每位数字用一个线程控制其变化，单击“停止”则所有标签数字停止变化。swing

以下内容由ChatGPT生成
```java
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class NumberChanger extends JFrame {
    private JLabel[] labels = new JLabel[6];  // 6 个标签
    private Thread[] threads = new Thread[6]; // 每个标签对应一个线程
    private boolean running = true;          // 控制线程是否运行

    public NumberChanger() {
        // 设置窗口标题、布局和关闭操作
        setTitle("数字变化程序");
        setLayout(new GridLayout(2, 3, 10, 10)); // 网格布局：2 行 3 列
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(400, 200);

        // 创建标签并添加到窗口中
        for (int i = 0; i < labels.length; i++) {
            labels[i] = new JLabel("0", SwingConstants.CENTER); // 标签默认显示 "0"
            labels[i].setFont(new Font("Arial", Font.BOLD, 30)); // 设置字体和大小
            labels[i].setBorder(BorderFactory.createLineBorder(Color.BLACK));
            add(labels[i]);
        }

        // 创建并启动每个标签对应的线程
        for (int i = 0; i < threads.length; i++) {
            final int index = i; // 保存索引供线程使用
            threads[i] = new Thread(() -> {
                while (true) {
                    if (!running) break; // 如果运行标志为 false，退出线程
                    int randomNum = (int) (Math.random() * 10); // 生成随机数字 0～9
                    labels[index].setText(String.valueOf(randomNum)); // 更新标签
                    try {
                        Thread.sleep(500); // 每隔 500 毫秒更新一次
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt(); // 恢复中断状态
                        break;
                    }
                }
            });
            threads[i].start(); // 启动线程
        }

        // 创建 "停止" 按钮
        JButton stopButton = new JButton("停止");
        stopButton.setFont(new Font("Arial", Font.BOLD, 20));
        stopButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                running = false; // 设置运行标志为 false
            }
        });

        // 添加按钮到窗口
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(stopButton);
        add(buttonPanel);

        // 显示窗口
        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(NumberChanger::new); // 启动程序
    }
}
```
用的是JPanel包。

关于volitile关键字，以下内容由ChatGPT生成：
```
class StopThread {
    private volatile boolean stop = false;

    public void stopThread() {
        stop = true;
    }

    public void run() {
        while (!stop) {
            // 线程运行
        }
    }
}
```

# 给出一份2022级版的答案
## 计算各个图形的面积
```java
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
```
## 学生信息管理系统
```
import java.util.*;

/**
 * 定义学生类 Student，用于存储学生信息和计算相关数据。
 */
class Student {
    // 私有成员变量，存储学生信息
    private String no; // 学号
    private String name; // 姓名
    private int age; // 年龄
    private double advanced; // 高级课程成绩
    private double ds; // 数据结构成绩
    private double english; // 英语成绩
    private double physics; // 物理成绩

    // 学号的 getter 和 setter
    public String getNo() {
        return no;
    }

    public void setNo(String no) {
        this.no = no;
    }

    // 姓名的 getter 和 setter
    public String getName() {
        return name;
    }

    public void setNmae(String name) { // 注意：此处原代码有拼写错误，应改为 setName
        this.name = name;
    }

    // 年龄的 getter 和 setter
    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    // 高级课程成绩的 getter 和 setter
    public double getAdvanced() {
        return advanced;
    }

    public void setAdvanced(double advanced) {
        this.advanced = advanced;
    }

    // 数据结构成绩的 getter 和 setter
    public double getDs() {
        return ds;
    }

    public void setDs(double ds) {
        this.ds = ds;
    }

    // 英语成绩的 getter 和 setter
    public double getEnglish() {
        return english;
    }

    public void setEnglish(double english) {
        this.english = english;
    }

    // 物理成绩的 getter 和 setter
    public double getPhysics() {
        return physics;
    }

    public void setPhysics(double physics) {
        this.physics = physics;
    }

    /**
     * 计算学生总成绩。
     * 总成绩 = 50% 高级课程成绩 + 40% 英语成绩 + 50% 物理成绩
     * @return 总成绩
     */
    public double getTotal() {
        return 0.5 * this.advanced + 0.4 * this.english + 0.5 * this.physics;
    }

    /**
     * 增加学生年龄（增长 1 岁）。
     */
    public void grow() {
        this.age++;
    }

    /**
     * 返回学生信息的字符串表示。
     * @return 学生信息字符串
     */
    @Override
    public String toString() {
        StringBuffer sb = new StringBuffer();
        sb.append("no:") // 学号
            .append(this.no)
            .append(", name:") // 姓名
            .append(this.name)
            .append(", advanced:") // 高级课程成绩
            .append(this.advanced)
            .append(", ds:") // 数据结构成绩
            .append(this.ds)
            .append(", english:") // 英语成绩
            .append(this.english)
            .append(", physics:") // 物理成绩
            .append(this.physics);
        return sb.toString();
    }
}

/**
 * 学生管理类，用于管理多个学生信息。
 */
public class Question2Pro {
    private Student[] students; // 存储学生对象的数组

    /**
     * 构造方法，初始化学生数组为空数组。
     */
    public Question2Pro() {
        this.students = new Student[0];
    }

    /**
     * 添加一个学生到数组中。
     * @param student 要添加的学生对象
     */
    public void addStudent(Student student) {
        int len = this.students.length;
        Student[] students = new Student[len + 1]; // 创建新数组，长度比原数组多 1
        for (int i = 0; i < len; i++) {
            students[i] = this.students[i]; // 复制原数组内容
        }
        students[len] = student; // 将新学生添加到数组末尾
        this.students = students; // 替换原数组
    }

    /**
     * 所有学生年龄增长 1 岁。
     */
    public void grow() {
        for (Student s : this.students) {
            s.grow(); // 调用每个学生的 grow 方法
        }
    }

    /**
     * 打印所有学生的信息。
     */
    public void print() {
        for (Student s : this.students) {
            System.out.println(s); // 调用每个学生的 toString 方法
        }
    }

    /**
     * 按照学生总成绩从小到大排序。
     */
    public void sort() {
        Arrays.sort(this.students, new Comparator<Student>() {
            @Override
            public int compare(Student a, Student b) {
                if (a.getTotal() < b.getTotal()) { // 比较总成绩
                    return -1; // a 的总成绩小于 b
                } else if (a.getTotal() > b.getTotal()) {
                    return 1; // a 的总成绩大于 b
                } else {
                    return 0; // 总成绩相等
                }
            }
        });
    }

    /**
     * 主方法，测试学生管理功能。
     * @param args 命令行参数
     */
    public static void main(String[] args) {
        Question2Pro manager = new Question2Pro(); // 创建学生管理对象

        // 创建第一个学生并初始化数据
        Student s = new Student();
        s.setNo("12345");
        s.setNmae("1");
        s.setAge(92);
        s.setAdvanced(11);
        s.setDs(12);
        s.setEnglish(13);
        s.setPhysics(14);
        manager.addStudent(s); // 添加到管理器

        // 创建第二个学生并初始化数据
        s = new Student();
        s.setNo("22345");
        s.setNmae("3");
        s.setAge(192);
        s.setAdvanced(111);
        s.setDs(112);
        s.setEnglish(113);
        s.setPhysics(114);
        manager.addStudent(s); // 添加到管理器

        // 所有学生年龄增长 1 岁
        manager.grow();

        // 打印学生信息
        manager.print();

        // 按总成绩排序
        manager.sort();

        // 打印排序后的学生信息
        manager.print();
    }
}
```
## 读入一行统计不同单词和出现次数
```
import java.util.*; // 导入 Java 实用工具包

/**
 * Question3Pro 类：用于统计输入字符串中每个单词的出现次数。
 */
class Question3Pro {
    public static void main(String[] args) {
        // 创建一个 HashMap，用于存储单词及其对应的出现次数
        Map<String, Integer> cnt = new HashMap<>();

        // 创建 Scanner 对象，用于从控制台读取输入
        Scanner scanner = new Scanner(System.in);

        // 提示用户输入一行文本
        System.out.println("请输入一段文本：");

        // 读取用户输入的整行字符串
        String str = scanner.nextLine();

        /**
         * 使用正则表达式 "[\\W]" 对输入字符串进行分割：
         * - \\W 表示非单词字符（即非字母、数字或下划线），如空格、标点符号等
         * - 分割后的结果存储在字符串数组 words 中
         */
        String words[] = str.split("[\\W]");

        // 遍历分割后的每个单词
        for (String x : words) {
            // 如果单词为空字符串，则跳过
            if (x.isEmpty()) continue;

            // 判断 HashMap 中是否已包含该单词
            if (cnt.containsKey(x)) {
                // 如果包含，更新该单词的计数值（加 1）
                cnt.put(x, cnt.get(x) + 1);
            } else {
                // 如果不包含，将该单词加入 HashMap，初始计数值为 1
                cnt.put(x, 1);
            }
        }

        // 打印 HashMap 中存储的单词及其出现次数
        System.out.println("单词统计结果：" + cnt);

        // 关闭 Scanner 对象，防止资源泄漏
        scanner.close();
    }
}
```
## 1500长的绳子每天剪掉1/5
```
/**
 * Question4Pro 类：计算每天切割某物体长度的操作所需的天数，直到长度小于指定值。
 */
public class Question4Pro {

    /**
     * cut 方法：模拟每天减少物体长度的过程，计算操作天数。
     * 
     * @return 需要的天数。
     */
    public static int cut() {
        // 初始化操作天数为 0
        int d = 0;

        // 初始长度设置为 150000
        for (double l = 150000;; l = l - l / 5, d++) {
            // 打印当前长度，便于调试和查看过程
            System.out.println("当前长度 l: " + l);

            /**
             * 判断条件：
             * - 如果当前长度在 [0, 1.25) 区间内，则结束循环。
             * - l >= 0 是为了确保长度非负。
             * - l < 1.25 是最终的停止条件。
             */
            if (l >= 0 && l < 1.25) {
                break;
            }
        }

        // 返回总共需要的天数
        return d;
    }

    /**
     * 主方法：程序的入口，调用 cut 方法并输出结果。
     */
    public static void main(String[] args) {
        // 打印计算所需的总天数
        System.out.println("所需天数: " + cut());
    }
}
```
## 汽车牌照选号
```
import javax.swing.*; // 导入用于创建图形界面的 Swing 包
import java.awt.event.ActionEvent; // 导入用于处理按钮事件的类
import java.awt.event.ActionListener; // 导入事件监听器接口
import java.util.*; // 导入实用工具类
import java.awt.*; // 导入 AWT 包，用于布局管理等

/**
 * 主类，继承 JFrame，用于创建图形界面并管理生成器线程。
 */
public class Question5Pro extends JFrame {
    private JLabel digits[] = new JLabel[5]; // 用于显示随机字符的标签数组
    private Generator generators[] = new Generator[5]; // 用于生成随机字符的生成器线程数组

    /**
     * 构造方法，调用 create 方法初始化界面。
     */
    public Question5Pro() {
        super(); // 调用父类构造方法
        this.create(); // 创建和初始化界面
    }

    /**
     * 创建并初始化图形界面，包括标签、按钮和线程。
     */
    private void create() {
        this.getContentPane().setLayout(new GridLayout(1, 6)); // 设置布局为 1 行 6 列

        // 创建 5 个 JLabel 标签并添加到界面中
        for (int i = 0; i < 5; i++) {
            digits[i] = new JLabel(); // 初始化标签
            digits[i].setHorizontalAlignment(SwingConstants.CENTER); // 设置文本居中显示
            this.getContentPane().add(digits[i]); // 添加标签到界面
        }

        // 创建一个停止按钮，用于停止所有线程
        JButton stop = new JButton("Stop");
        stop.addActionListener(new ActionListener() { // 为按钮添加事件监听器
            public void actionPerformed(ActionEvent e) {
                for (int i = 0; i < 5; i++) { // 遍历所有生成器
                    generators[i].stop(); // 调用生成器的 stop 方法停止线程
                }
            }
        });
        this.getContentPane().add(stop); // 添加按钮到界面

        // 设置窗口大小和属性
        this.setSize(600, 100); // 设置窗口大小
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE); // 设置关闭操作
        this.setVisible(true); // 设置窗口可见

        // 创建 5 个生成器线程并启动
        for (int i = 0; i < 5; i++) {
            generators[i] = new Generator(digits[i]); // 初始化生成器并绑定对应的标签
            Thread t = new Thread(generators[i]); // 创建新线程
            t.start(); // 启动线程
        }
    }

    /**
     * 主方法，程序入口点。
     * 使用 SwingUtilities.invokeLater 确保线程安全的 Swing 操作。
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new Question5Pro(); // 创建主窗口实例
            }
        });
    }
}

/**
 * 生成器类，实现 Runnable 接口，用于生成随机字符。
 */
class Generator implements Runnable {
    // 定义一个字符数组，包含 0-9 和 a-z
    private static final char[] CHARS = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z'
    };

    private volatile boolean running = true; // 标志位，用于控制线程的运行状态
    private JLabel target; // 目标标签，用于显示随机字符
    private Random random; // 随机数生成器

    /**
     * 构造方法，初始化目标标签和随机数生成器。
     *
     * @param target 要显示随机字符的 JLabel。
     */
    public Generator(JLabel target) {
        this.target = target; // 绑定目标标签
        random = new Random(System.currentTimeMillis()); // 初始化随机数生成器
    }

    /**
     * 停止方法，设置标志位为 false，停止线程。
     */
    public void stop() {
        running = false; // 设置标志位为 false
    }

    /**
     * 线程运行方法，不断生成随机字符并更新到目标标签。
     */
    public void run() {
        try {
            // 当标志位为 true 并且线程未被中断时，持续运行
            while (running && !Thread.interrupted()) {
                int next = random.nextInt(CHARS.length); // 随机生成一个字符的索引
                // 使用 SwingUtilities.invokeLater 确保线程安全的 Swing 操作
                SwingUtilities.invokeLater(new Runnable() {
                    public void run() {
                        target.setText("" + CHARS[next]); // 更新目标标签的文本
                    }
                });
                Thread.sleep(100); // 暂停线程 100 毫秒，降低字符切换速度
            }
        } catch (Exception e) {
            e.printStackTrace(); // 打印异常堆栈信息
        }
    }
}
```