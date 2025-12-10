package ssm.crud;
// ClassService.java

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ClassService {

    private SqlSessionFactory sqlSessionFactory;
    private ClassMapper classMapper;

    public ClassService() {
        try {
            // 加载MyBatis配置文件
            String resource = "mybatiscrud-config.xml";
            InputStream inputStream = Resources.getResourceAsStream(resource);
            sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
            // 获取Mapper
            SqlSession sqlSession = sqlSessionFactory.openSession();
            classMapper = sqlSession.getMapper(ClassMapper.class);
        } catch (IOException e) {
            throw new RuntimeException("初始化MyBatis失败", e);
        }
    }

    public ClassService(SqlSessionFactory sqlSessionFactory) {
        this.sqlSessionFactory = sqlSessionFactory;
        SqlSession sqlSession = sqlSessionFactory.openSession();
        classMapper = sqlSession.getMapper(ClassMapper.class);
    }

    // ========== 查询操作示例 ==========

    /**
     * 根据ID查询班级信息（联表查询方式）
     */
    public Classes getClassById(int id) {
        try (SqlSession sqlSession = sqlSessionFactory.openSession()) {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            return mapper.getClass(id);
        }
    }

    /**
     * 根据ID查询班级信息（嵌套查询方式）
     */
    public Classes getClassById2(int id) {
        try (SqlSession sqlSession = sqlSessionFactory.openSession()) {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            return mapper.getClass2(id);
        }
    }

    /**
     * 查询包含学生和老师信息的班级
     */
    public Classes getClassWithDetails(int id) {
        try (SqlSession sqlSession = sqlSessionFactory.openSession()) {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            return mapper.getClass3(id);
        }
    }

    /**
     * 分页查询班级
     */
    public List<Classes> getClassesByPage(int pageNum, int pageSize) {
        try (SqlSession sqlSession = sqlSessionFactory.openSession()) {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            Map<String, Object> params = new HashMap<>();
            params.put("offset", (pageNum - 1) * pageSize);
            params.put("pageSize", pageSize);
            return mapper.getClassesByPage(params);
        }
    }

    /**
     * 根据名称模糊查询班级
     */
    public List<Classes> searchClassesByName(String name) {
        try (SqlSession sqlSession = sqlSessionFactory.openSession()) {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            return mapper.getClassesByName(name);
        }
    }

    // ========== 新增操作示例 ==========

    /**
     * 添加新班级
     */
    public boolean addClass(Classes classes) {
        SqlSession sqlSession = sqlSessionFactory.openSession();
        try {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            int result = mapper.insertClass(classes);
            sqlSession.commit();
            return result > 0;
        } catch (Exception e) {
            sqlSession.rollback();
            e.printStackTrace();
            return false;
        } finally {
            sqlSession.close();
        }
    }

    /**
     * 批量添加班级
     */
    public boolean batchAddClasses(List<Classes> classesList) {
        SqlSession sqlSession = sqlSessionFactory.openSession();
        try {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            int result = mapper.batchInsertClasses(classesList);
            sqlSession.commit();
            return result == classesList.size();
        } catch (Exception e) {
            sqlSession.rollback();
            e.printStackTrace();
            throw new RuntimeException("批量添加班级失败", e);
        } finally {
            sqlSession.close();
        }
    }

    // ========== 修改操作示例 ==========

    /**
     * 更新班级信息
     */
    public boolean updateClass(Classes classes) {
        SqlSession sqlSession = sqlSessionFactory.openSession();
        try {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            int result = mapper.updateClass(classes);
            sqlSession.commit();
            return result > 0;
        } catch (Exception e) {
            sqlSession.rollback();
            e.printStackTrace();
            return false;
        } finally {
            sqlSession.close();
        }
    }

    /**
     * 更新班级名称
     */
    public boolean updateClassName(int classId, String newName) {
        SqlSession sqlSession = sqlSessionFactory.openSession();
        try {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            Map<String, Object> params = new HashMap<>();
            params.put("id", classId);
            params.put("name", newName);
            int result = mapper.updateClassName(params);
            sqlSession.commit();
            return result > 0;
        } catch (Exception e) {
            sqlSession.rollback();
            e.printStackTrace();
            return false;
        } finally {
            sqlSession.close();
        }
    }

    /**
     * 更新班级班主任
     */
    public boolean updateClassTeacher(int classId, int teacherId) {
        SqlSession sqlSession = sqlSessionFactory.openSession();
        try {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            Map<String, Object> params = new HashMap<>();
            params.put("classId", classId);
            params.put("teacherId", teacherId);
            int result = mapper.updateClassTeacher(params);
            sqlSession.commit();
            return result > 0;
        } catch (Exception e) {
            sqlSession.rollback();
            e.printStackTrace();
            return false;
        } finally {
            sqlSession.close();
        }
    }

    // ========== 删除操作示例 ==========

    /**
     * 根据ID删除班级
     */
    public boolean deleteClass(int classId) {
        SqlSession sqlSession = sqlSessionFactory.openSession();
        try {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            int result = mapper.deleteClassById(classId);
            sqlSession.commit();
            return result > 0;
        } catch (Exception e) {
            sqlSession.rollback();
            e.printStackTrace();
            return false;
        } finally {
            sqlSession.close();
        }
    }

    /**
     * 根据名称删除班级
     */
    public boolean deleteClassByName(String className) {
        SqlSession sqlSession = sqlSessionFactory.openSession();
        try {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            int result = mapper.deleteClassByName(className);
            sqlSession.commit();
            return result > 0;
        } catch (Exception e) {
            sqlSession.rollback();
            e.printStackTrace();
            return false;
        } finally {
            sqlSession.close();
        }
    }

    /**
     * 批量删除班级
     */
    public boolean batchDeleteClasses(List<Integer> classIds) {
        SqlSession sqlSession = sqlSessionFactory.openSession();
        try {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            int result = mapper.batchDeleteClasses(classIds);
            sqlSession.commit();
            return result > 0;
        } catch (Exception e) {
            sqlSession.rollback();
            e.printStackTrace();
            throw new RuntimeException("批量删除班级失败", e);
        } finally {
            sqlSession.close();
        }
    }

    /**
     * 根据教师ID删除对应的班级
     */
    public boolean deleteClassesByTeacher(int teacherId) {
        SqlSession sqlSession = sqlSessionFactory.openSession();
        try {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            int result = mapper.deleteClassesByTeacherId(teacherId);
            sqlSession.commit();
            return result > 0;
        } catch (Exception e) {
            sqlSession.rollback();
            e.printStackTrace();
            return false;
        } finally {
            sqlSession.close();
        }
    }

    // ========== 业务方法示例 ==========

    /**
     * 检查班级名称是否已存在
     */
    public boolean isClassNameExists(String className) {
        try (SqlSession sqlSession = sqlSessionFactory.openSession()) {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            int count = mapper.checkClassNameExists(className);
            return count > 0;
        }
    }

    /**
     * 获取班级总数
     */
    public int getTotalClassCount() {
        try (SqlSession sqlSession = sqlSessionFactory.openSession()) {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            return mapper.countClasses();
        }
    }

    /**
     * 获取所有班级列表
     */
    public List<Classes> getAllClasses() {
        try (SqlSession sqlSession = sqlSessionFactory.openSession()) {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            return mapper.getAllClasses();
        }
    }

    /**
     * 获取教师信息
     */
    public Teacher getTeacher(int teacherId) {
        try (SqlSession sqlSession = sqlSessionFactory.openSession()) {
            ClassMapper mapper = sqlSession.getMapper(ClassMapper.class);
            return mapper.getTeacher(teacherId);
        }
    }
}