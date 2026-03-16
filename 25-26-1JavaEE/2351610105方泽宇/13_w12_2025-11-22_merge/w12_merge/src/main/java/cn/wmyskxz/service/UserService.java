package cn.wmyskxz.service;

import cn.wmyskxz.entity.User;

import java.util.List;

public interface UserService {
    public User findUserById(int id);
    public List<User> getAllUser();
    public void addUser(User p);
    public void deleteById(int id);
    public void deleteMuchByIds(List<String> lists);
    public void updateUser(User p);
}
