package me.gacl.mapping;

import java.util.List;
import me.gacl.domain.User;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

/**
 * @author gacl
 * ����sqlӳ��Ľӿڣ�ʹ��ע��ָ������Ҫִ�е�SQL
 */
public interface UserMapperI {

    //ʹ��@Insertע��ָ��add����Ҫִ�е�SQL
    @Insert("insert into users(name, age) values(#{name}, #{age})")
    public int add(User user);
    
    //ʹ��@Deleteע��ָ��deleteById����Ҫִ�е�SQL
    @Delete("delete from users where id=#{id}")
    public int deleteById(int id);
    
    //ʹ��@Updateע��ָ��update����Ҫִ�е�SQL
    @Update("update users set name=#{name},age=#{age} where id=#{id}")//err
    //@Update("update users set name=#{name},age=#{age} where id=#{id}")//ok
    public int update(User user);
    
    //ʹ��@Selectע��ָ��getById����Ҫִ�е�SQL
    @Select("select * from users where id=#{id}")
    public User getById(int id);
    
    //ʹ��@Selectע��ָ��getAll����Ҫִ�е�SQL
    @Select("select * from users")
    public List<User> getAll();
}