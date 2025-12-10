package com.example.mapper;
import com.example.entity.User;
import java.util.List;

public interface UserMapper {
    User selectUserById(Long id);
    List<User> selectAllUsers();
    void insertUser(User user);
    void updateUser(User user);
    void deleteUser(Long id);
}