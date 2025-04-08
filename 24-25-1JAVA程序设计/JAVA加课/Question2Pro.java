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