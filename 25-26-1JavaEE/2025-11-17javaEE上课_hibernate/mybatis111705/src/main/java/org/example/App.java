package org.example;

/**
 * Hello world!
 *
 */
import com.example.entity.User;
import com.example.mapper.UserMapper;
import com.example.utils.MyBatisUtil;
import org.apache.ibatis.session.SqlSession;


import java.util.List;
public class App 
{
    public static void main( String[] args )
    {
        System.out.println( "Hello World!" );
        try  {
            SqlSession sqlSession = MyBatisUtil.getSqlSession();
            UserMapper userMapper = sqlSession.getMapper(UserMapper.class);

            // 插入用户
            User newUser = new User("张三", "zhangsan@example.com");
            userMapper.insertUser(newUser);
            sqlSession.commit();
            System.out.println("插入用户ID: " + newUser.getId());

            // 查询所有用户
            List<User> users = userMapper.selectAllUsers();
            for(User user:users)
                System.out.println(user.toString());

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
