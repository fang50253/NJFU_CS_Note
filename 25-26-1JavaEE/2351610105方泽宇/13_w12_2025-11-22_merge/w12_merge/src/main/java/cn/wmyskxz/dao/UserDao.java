package cn.wmyskxz.dao;

import cn.wmyskxz.entity.User;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface UserDao {
    User findUserById(int id);

    List<User> getAllUsers();
    void addUser(User p);
    void deleteUser(int id);
    void deleteMuchByIds(@Param("lists") List<String> list);
    void updateUser(User p);
}
