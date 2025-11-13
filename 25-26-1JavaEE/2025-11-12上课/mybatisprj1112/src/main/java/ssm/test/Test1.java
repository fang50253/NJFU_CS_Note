package ssm.test;


import java.io.IOException;
import java.io.InputStream;
import java.io.Reader;
import java.util.List;

import ssm.test.User;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

public class Test1 {

    public static void main(String[] args) throws IOException {
        //mybatis�������ļ�
        String resource = "conf.xml";
        //ʹ�������������mybatis�������ļ�����Ҳ���ع�����ӳ���ļ���
        InputStream is = Test1.class.getClassLoader().getResourceAsStream(resource);
        //����sqlSession�Ĺ���
        SqlSessionFactory sessionFactory = new SqlSessionFactoryBuilder().build(is);
        //ʹ��MyBatis�ṩ��Resources�����mybatis�������ļ�����Ҳ���ع�����ӳ���ļ���
        //Reader reader = Resources.getResourceAsReader(resource); 
        //����sqlSession�Ĺ���
        //SqlSessionFactory sessionFactory = new SqlSessionFactoryBuilder().build(reader);
        //������ִ��ӳ���ļ���sql��sqlSession
        SqlSession session = sessionFactory.openSession();
        /**
         * ӳ��sql�ı�ʶ�ַ�����
         * me.gacl.mapping.userMapper��userMapper.xml�ļ���mapper��ǩ��namespace���Ե�ֵ��
         * getUser��select��ǩ��id����ֵ��ͨ��select��ǩ��id����ֵ�Ϳ����ҵ�Ҫִ�е�SQL
         */
//        String statement = "ssm.test.userMapper.getUser";//ӳ��sql�ı�ʶ�ַ���
//        //ִ�в�ѯ����һ��Ψһuser�����sql
//        User user = session.selectOne(statement, 3);
//        System.out.println(user);
//
//        String statement2 = "ssm.test.userMapper.addUser";//ok
//        User user2 = new User();
//        user2.setName("ffff second add332");
//        user2.setAge(38);
//        //ִ�в������
//        int retResult = session.insert(statement2,user2);
//        //�ֶ��ύ����
//        session.commit();
//        //ʹ��SqlSessionִ����SQL֮����Ҫ�ر�SqlSession
//        //session.close();
//        System.out.println(retResult);
//
//        String statement3 = "ssm.test.userMapper.getAllUsers";//err
//        //String statement = "ssm.test.userMapper.getAllUser";
//        //ִ�в�ѯ����������ѯ����Զ���װ��List<User>����
//        List<User> lstUsers = session.selectList(statement3);
//        //ʹ��SqlSessionִ����SQL֮����Ҫ�ر�SqlSession
//        session.commit();
//        //session.close();
//        System.out.println(lstUsers);
//
//        String statement5 ="ssm.test.userMapper.updateUser";//ӳ��sql�ı�ʶ�ַ���
//        User user5 = new User();
//        user5.setId(3);//ok
//        //user.setId(1113);//err
//        user5.setName("modify username 999");
//        user5.setAge(25);
//        //ִ���޸Ĳ���
//        int retResult4 = session.update(statement5,user5);
//
//        //ʹ��SqlSessionִ����SQL֮����Ҫ�ر�SqlSession
//        session.commit();
//        session.close();
//        System.out.println(retResult4);



        System.out.println("testDelete");
        SqlSession sqlSession = MyBatisUtil.getSqlSession(true);

        String statement = "ssm.test.userMapper.deleteUser";//ӳ��sql�ı�ʶ�ַ���
        //ִ��ɾ������
        int retResult = sqlSession.delete(statement,1);
        //ʹ��SqlSessionִ����SQL֮����Ҫ�ر�SqlSession
        sqlSession.commit();
        sqlSession.close();
        System.out.println(retResult);
    }
}