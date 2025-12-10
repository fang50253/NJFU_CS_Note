package ssm.crud;
public class Teacher {
    private Integer id;
    private String name;

    // 构造方法
    public Teacher() {}

    public Teacher(Integer id, String name) {
        this.id = id;
        this.name = name;
    }

    // getter和setter
    public Integer getId() { return id; }
    public void setId(Integer id) { this.id = id; }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }

    @Override
    public String toString() {
        return "Teacher{id=" + id + ", name='" + name + "'}";
    }
}