package ssm.test;

import org.apache.ibatis.session.SqlSession;
import org.junit.Test;
import java.util.Arrays;
import java.util.List;

public class TestBlogCRUD {

    // 新增博客
    //@Test
    public void testInsert() {
        try (SqlSession session = MyBatisUtil.getSqlSession(true)) {
            BlogMapper mapper = session.getMapper(BlogMapper.class);
            Blog blog = new Blog("MyBatis", "是优秀的持久层框架", "张三");
            int rows = mapper.insert(blog);
            System.out.println("新增成功，ID: " + blog.getId() + "，影响行数: " + rows);
        }
    }

    // 更新博客
    //@Test
    public void testUpdate() {
        try (SqlSession session = MyBatisUtil.getSqlSession(true)) {
            BlogMapper mapper = session.getMapper(BlogMapper.class);
            Blog blog = new Blog();
            blog.setId(3L);
            blog.setTitle("MyBatis进阶教程");
            blog.setReadCount(100);
            int rows = mapper.update(blog);
            System.out.println("更新成功，影响行数: " + rows);
        }
    }

    // 查询博客
    //@Test
    public void testSelect() {
        try (SqlSession session = MyBatisUtil.getSqlSession()) {
            BlogMapper mapper = session.getMapper(BlogMapper.class);

            // 单条查询
            Blog blog = mapper.selectById(3L);
            System.out.println("单条查询: " + blog);

            // 条件查询
            List<Blog> blogs = mapper.selectByCondition("MyBatis", "张三");
            System.out.println("条件查询结果: ");
            blogs.forEach(System.out::println);
        }
    }

    // 删除博客
    @Test
    public void testDelete() {
        try (SqlSession session = MyBatisUtil.getSqlSession(true)) {
            BlogMapper mapper = session.getMapper(BlogMapper.class);

            // 单条删除
            int retResult = mapper.deleteById(2L);
            System.out.println("单条删除影响行数: " + retResult);

            // 批量删除
            List<Long> ids = Arrays.asList(3L, 4L);
            int batchRows = mapper.batchDelete(ids);
            System.out.println("批量删除影响行数: " + batchRows);
        }
    }
}