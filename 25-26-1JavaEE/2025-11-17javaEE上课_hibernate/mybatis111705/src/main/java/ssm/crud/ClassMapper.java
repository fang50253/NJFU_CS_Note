package ssm.crud;

import java.util.List;
import java.util.Map;

public interface ClassMapper {

    // ========== 查询操作 ==========
    Classes getClass(int id);
    Classes getClass2(int id);
    Classes getClass3(int id);
    Classes getClass4(int id);
    Teacher getTeacher(int id);
    Student getStudent(int id);
    List<Classes> getAllClasses();
    List<Classes> getClassesByName(String name);
    List<Classes> getClassesByPage(Map<String, Object> params);
    int countClasses();
    int checkClassNameExists(String name);

    // ========== 新增操作 ==========
    int insertClass(Classes classes);
    int batchInsertClasses(List<Classes> classesList);

    // ========== 修改操作 ==========
    int updateClass(Classes classes);
    int updateClassName(Map<String, Object> params);
    int updateClassTeacher(Map<String, Object> params);

    // ========== 删除操作 ==========
    int deleteClassById(int id);
    int deleteClassByName(String name);
    int batchDeleteClasses(List<Integer> ids);
    int deleteClassesByTeacherId(int teacherId);
}