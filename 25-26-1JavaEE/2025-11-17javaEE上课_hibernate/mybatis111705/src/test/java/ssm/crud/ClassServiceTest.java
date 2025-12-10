package ssm.crud;


import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

public class ClassServiceTest {

    private ClassService classService;

    @Before
    public void setUp() {
        classService = new ClassService();
    }

   // @Test
    public void testCRUDOperations() {
        System.out.println("=== MyBatis CRUD 操作测试 ===");

        // 1. 创建教师对象
        Teacher teacher = new Teacher(1, "张老师");

        // 2. 测试新增操作
        System.out.println("\n--- 测试新增操作 ---");
        Classes newClass = new Classes();
        newClass.setName("三年级二班");
        newClass.setTeacher(teacher);

        boolean addResult = classService.addClass(newClass);
        System.out.println("添加班级结果: " + addResult);
        if (addResult) {
            System.out.println("新增班级ID: " + newClass.getId());
        }

        // 3. 测试查询操作
        System.out.println("\n--- 测试查询操作 ---");
        Classes foundClass = classService.getClassById(newClass.getId());
        System.out.println("查询到的班级: " + foundClass);

        // 4. 测试修改操作
        System.out.println("\n--- 测试修改操作 ---");
        foundClass.setName("三年级二班(更新)");
        boolean updateResult = classService.updateClass(foundClass);
        System.out.println("更新班级结果: " + updateResult);

        // 验证更新结果
        Classes updatedClass = classService.getClassById(foundClass.getId());
        System.out.println("更新后的班级: " + updatedClass);

        // 5. 测试批量操作
        System.out.println("\n--- 测试批量操作 ---");
        List<Classes> classList = new ArrayList<>();
        Classes class1 = new Classes();
        class1.setName("四年级一班");
        class1.setTeacher(teacher);

        Classes class2 = new Classes();
        class2.setName("四年级二班");
        class2.setTeacher(teacher);

        classList.add(class1);
        classList.add(class2);

        boolean batchAddResult = classService.batchAddClasses(classList);
        System.out.println("批量添加结果: " + batchAddResult);

        // 6. 测试分页查询
        System.out.println("\n--- 测试分页查询 ---");
        List<Classes> pageClasses = classService.getClassesByPage(1, 10);
        System.out.println("第一页班级列表:");
        for (Classes cls : pageClasses) {
            System.out.println("  " + cls);
        }

        // 7. 测试删除操作
        System.out.println("\n--- 测试删除操作 ---");
        boolean deleteResult = classService.deleteClass(newClass.getId());
        System.out.println("删除班级结果: " + deleteResult);

        // 8. 测试统计功能
        System.out.println("\n--- 测试统计功能 ---");
        int totalCount = classService.getTotalClassCount();
        System.out.println("班级总数: " + totalCount);

        System.out.println("\n=== CRUD 测试完成 ===");
    }

    @Test
    public void testAdvancedQueries() {
        System.out.println("=== 高级查询测试 ===");

        // 测试关联查询
        Classes classWithDetails = classService.getClassWithDetails(1);
        System.out.println("班级详情: " + classWithDetails);

        // 测试模糊查询
        List<Classes> searchResults = classService.searchClassesByName("三");
        System.out.println("模糊查询结果:");
        for (Classes cls : searchResults) {
            System.out.println("  " + cls);
        }

        // 测试存在性检查
        boolean exists = classService.isClassNameExists("三年级一班");
        System.out.println("班级名称是否存在: " + exists);
    }

    @Test
    public void testComplexOperations() {
        System.out.println("=== 复杂操作测试 ===");

        // 测试嵌套查询
        Classes classWithNested = classService.getClassById2(1);
        System.out.println("嵌套查询结果: " + classWithNested);

        // 测试更新特定字段
        boolean updateNameResult = classService.updateClassName(1, "新班级名称");
        System.out.println("更新班级名称结果: " + updateNameResult);

        // 测试更新班主任
        boolean updateTeacherResult = classService.updateClassTeacher(1, 2);
        System.out.println("更新班主任结果: " + updateTeacherResult);

        // 测试批量删除
        List<Integer> idsToDelete = new ArrayList<>();
        idsToDelete.add(10);
        idsToDelete.add(11);
        boolean batchDeleteResult = classService.batchDeleteClasses(idsToDelete);
        System.out.println("批量删除结果: " + batchDeleteResult);
    }

    @Test
    public void testAllOperations() {
        System.out.println("=== 完整操作流程测试 ===");

        // 1. 查询现有数据
        System.out.println("\n1. 查询现有班级:");
        List<Classes> allClasses = classService.getAllClasses();
        for (Classes cls : allClasses) {
            System.out.println("   " + cls);
        }

        // 2. 添加新班级
        System.out.println("\n2. 添加新班级:");
        Teacher teacher = classService.getTeacher(1);
        Classes newClass = new Classes();
        newClass.setName("测试班级");
        newClass.setTeacher(teacher);

        boolean addSuccess = classService.addClass(newClass);
        System.out.println("   添加结果: " + addSuccess);

        if (addSuccess) {
            // 3. 查询新添加的班级
            System.out.println("\n3. 查询新添加的班级:");
            Classes addedClass = classService.getClassById(newClass.getId());
            System.out.println("   查询结果: " + addedClass);

            // 4. 更新班级信息
            System.out.println("\n4. 更新班级信息:");
            addedClass.setName("测试班级(已更新)");
            boolean updateSuccess = classService.updateClass(addedClass);
            System.out.println("   更新结果: " + updateSuccess);

            // 5. 删除测试班级
            System.out.println("\n5. 删除测试班级:");
            boolean deleteSuccess = classService.deleteClass(addedClass.getId());
            System.out.println("   删除结果: " + deleteSuccess);
        }

        // 6. 最终统计
        System.out.println("\n6. 最终统计:");
        int finalCount = classService.getTotalClassCount();
        System.out.println("   最终班级总数: " + finalCount);

        System.out.println("\n=== 完整操作流程测试完成 ===");
    }
}