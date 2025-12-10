package ssm.crud;

import java.util.List;

public class Classes {
    private Integer id;
    private String name;
    private Teacher teacher;
    private List<Student> students;

    // 构造方法
    public Classes() {}

    public Classes(Integer id, String name) {
        this.id = id;
        this.name = name;
    }

    // getter和setter
    public Integer getId() { return id; }
    public void setId(Integer id) { this.id = id; }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public Teacher getTeacher() { return teacher; }
    public void setTeacher(Teacher teacher) { this.teacher = teacher; }
    public List<Student> getStudents() { return students; }
    public void setStudents(List<Student> students) { this.students = students; }

    @Override
    public String toString() {
        return "Classes{id=" + id + ", name='" + name + "', teacher=" + teacher +
                ", students=" + students + "}";
    }
}