package cn.wmyskxz.service;

//import javax.annotation.Resource;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import cn.wmyskxz.dao.UserDao;
import cn.wmyskxz.entity.User;

import java.util.List;

@Service("userService")
public class UserServiceImpl implements UserService {

    //@Resource
    @Autowired
    private UserDao userDao;

    public User findUserById(int id) {
        return userDao.findUserById(id);
    }

    @Override
    public List<User> getAllUser() {
        System.out.println("UserServiceImpl ...getAllUser ");
        return userDao.getAllUsers();
    }
    public void addUser(User p){
        System.out.println("UserServiceImpl ...addUser ");
         userDao.addUser(p);
        //return ;
    }

    public void deleteById(int id){
        System.out.println("UserServiceImpl ...deleteById ");
        userDao.deleteUser(id);
    }

    public void deleteMuchByIds(List<String> lists){
        System.out.println("UserServiceImpl ...deleteMuchByIds ");
        userDao.deleteMuchByIds(lists);
    }
    public void updateUser(User p){
        userDao.updateUser(p);
    }

}
