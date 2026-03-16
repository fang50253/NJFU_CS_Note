package ssm.test; 

/**
 * @author gacl
 * 定义student表所对应的实体类
 */
public class Student {

    //定义属性，和student表中的字段对应
    private int id;            //id===>s_id
    private String name;    //name===>s_name
    
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Student [id=" + id + ", name=" + name + "]";
    }
}