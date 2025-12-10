package ssm.test;
import org.apache.ibatis.session.SqlSession;
import org.junit.Test;
import java.util.List;
import ssm.test.User;
import ssm.test.MyBatisUtil;

public class TestCRUDByXmlMapper {

//	public static void main(String[] args) {
//		// TODO Auto-generated method stub
//		 TestCRUDByXmlMapper t=new  TestCRUDByXmlMapper();
//			 t.testAdd();
//	}
//


	    //@Test
	    public void testAdd(){
	        //SqlSession sqlSession = MyBatisUtil.getSqlSession(false);
	        SqlSession sqlSession = MyBatisUtil.getSqlSession(true);
	        /**
	         * ӳ��sql�ı�ʶ�ַ�����
	         * me.gacl.mapping.userMapper��userMapper.xml�ļ���mapper��ǩ��namespace���Ե�ֵ��
	         * addUser��insert��ǩ��id����ֵ��ͨ��insert��ǩ��id����ֵ�Ϳ����ҵ�Ҫִ�е�SQL
	         */
	        //String statement = "ssm.test.userMapper.addUserx";//err
			String statement = "ssm.test.userMapper.addUser";//ok
	        User user = new User();
	        user.setName("ffff second add2");
	        user.setAge(38);
	        //ִ�в������
	        int retResult = sqlSession.insert(statement,user);
	        //�ֶ��ύ����
	         sqlSession.commit();
	        //ʹ��SqlSessionִ����SQL֮����Ҫ�ر�SqlSession
	        sqlSession.close();
	        System.out.println(retResult);
	    }
	    
	    // @Test
	    public void testUpdate(){
	        SqlSession sqlSession = MyBatisUtil.getSqlSession(true);
	        System.out.println("testupdate");
	        String statement = "ssm.test.userMapper.updateUser";//ӳ��sql�ı�ʶ�ַ���
	        User user = new User();
	        //user.setId(3);//ok
			user.setId(1113);//err
	        user.setName("modify username");
	        user.setAge(25);
	        //ִ���޸Ĳ���
	        int retResult = sqlSession.update(statement,user);
	        //ʹ��SqlSessionִ����SQL֮����Ҫ�ر�SqlSession
	        sqlSession.commit();
	        sqlSession.close();
	        System.out.println(retResult);
	    }
	     
	  //  @Test
	    public void testDelete(){
	        SqlSession sqlSession = MyBatisUtil.getSqlSession(true);
	       
	        String statement = "ssm.test.userMapper.deleteUser";//ӳ��sql�ı�ʶ�ַ���
	        //ִ��ɾ������
	        int retResult = sqlSession.delete(statement,5);
	        //ʹ��SqlSessionִ����SQL֮����Ҫ�ر�SqlSession
	        sqlSession.commit();
	        sqlSession.close();
	        System.out.println(retResult);
	    }
	  
	    @Test
	    public void testGetAll(){
	        SqlSession sqlSession = MyBatisUtil.getSqlSession();
	      
	        String statement = "ssm.test.userMapper.getAllUsers";//err
			//String statement = "ssm.test.userMapper.getAllUser";
	        //ִ�в�ѯ����������ѯ����Զ���װ��List<User>����
	        List<User> lstUsers = sqlSession.selectList(statement);
	        //ʹ��SqlSessionִ����SQL֮����Ҫ�ر�SqlSession
	        sqlSession.commit();
	        sqlSession.close();
	        System.out.println(lstUsers);
	    }
}