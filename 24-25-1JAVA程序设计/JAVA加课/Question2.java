
import java.util.*;
class Student{
    private String no;
    private String name;
    private int age;
    private double advanced;
    private double ds;
    private double english;
    private double physics;
    public String getNo(){
        return no;
    }
    public void setNo(String no){
        this.no=no;
    }
    public String getName(){
        return name;
    }
    public void setNmae(String name){
        this.name=name;
    }
    public int getAge(){
        return age;
    }
    public void setAge(int age){
        this.age=age;
    }
    public double getAdvanced(){
        return advanced;
    }
    public void setAdvanced(double advanced){
        this.advanced=advanced;
    }
    public double getDs(){
        return ds;
    }
    public void setDs(double ds){
        this.ds=ds;
    }
    public double getEnglish(){
        return english;
    }
    public void setEnglish(double english){
        this.english=english;
    }
    public double getPhysics(){
        return physics;
    }
    public void setPhysics(double physics){
        this.physics=physics;
    }
    public double getTotal(){
        return .5*this.advanced+.4*this.english+.5*this.physics;
    }
    public void grow(){
        this.age++;
    }
    @Override
    public String toString(){
        StringBuffer sb=new StringBuffer();
        sb.append("no:")
            .append(this.no)
            .append(",name:")
            .append(this.name)
            .append(",advanced:")
            .append(this.advanced)
            .append(",ds:")
            .append(this.ds)
            .append(",english")
            .append(this.english)
            .append(",physics")
            .append(this.physics);
        return sb.toString();
    }
}
public class Question2{
    private Student[] students;
    public Question2(){
        this.students=new Student[0];
    }
    public void addStudent(Student student){
        int len=this.students.length;
        Student[] students=new Student[len+1];
        for (int i=0;i<len;i++){
            students[i]=this.students[i];
        }
        students[len]=student;
        this.students=students;
    }
    public void grow(){
        for(Student s:this.students){
            s.grow();
        }
    }
    public void print(){
        for(Student s:this.students){
            System.out.println(s);
        }
    }
    public void sort(){
        Arrays.sort(this.students,new Comparator<Student>(){
            @Override
            public int compare(Student a,Student b){
                if(a.getTotal()<b.getTotal()){
                    return -1;
                }
                else if(a.getTotal()>b.getTotal()){
                    return 1;
                }
                else{
                    return 0;
                }
            };
        });
    }
    public static void main(String[] args){
        Question2 manager=new Question2();
        Student s=new Student();
        s.setNo("12345");
        s.setNmae("1");
        s.setAge(92);
        s.setAdvanced(11);
        s.setDs(12);
        s.setEnglish(13);
        s.setPhysics(14);
        manager.addStudent(s);
        s=new Student();
        s.setNo("22345");
        s.setNmae("3");
        s.setAge(192);
        s.setAdvanced(111);
        s.setDs(112);
        s.setEnglish(113);
        s.setPhysics(114);
        manager.addStudent(s);
        manager.grow();
        manager.print();
        manager.sort();
        manager.print();
    }
}