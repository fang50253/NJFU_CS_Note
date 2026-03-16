package ssm.test;

import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;

import static org.junit.Assert.*;

public class BlogTest {

    private SqlSessionFactory sqlSessionFactory;
    private SqlSession session;
    private BlogMapper blogMapper;

    // 初始化 MyBatis 环境（测试前执行）
    @Before
    public void init() {
        try {
            // 读取 MyBatis 配置文件
            String resource = "conf.xml";
            InputStream inputStream = org.apache.ibatis.io.Resources.getResourceAsStream(resource);

            // 创建 SqlSessionFactory
            sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);

            // 打开 SqlSession（自动提交事务）
            session = sqlSessionFactory.openSession(true);

            // 获取 Mapper 接口实例
            blogMapper = session.getMapper(BlogMapper.class);

            System.out.println("===== 测试环境初始化完成 =====");
        } catch (IOException e) {
            e.printStackTrace();
            fail("初始化失败：" + e.getMessage());
        }
    }

    // 测试新增博客（无参构造器 + setter 赋值）
    @Test
    public void testInsertBlog() {
        System.out.println("\n===== 开始测试新增博客 =====");

        // 正确方式：无参构造器 + setter 赋值
        Blog blog = new Blog();
        blog.setTitle("MyBatis 实战教程");
        blog.setContent("本文详细介绍 MyBatis 框架的核心用法，包括 CRUD 操作、动态 SQL、关联查询等...");
        blog.setAuthor("技术达人");

        // 执行新增
        int result = blogMapper.insert(blog);

        // 验证结果
        assertEquals(1, result); // 新增成功返回 1
        assertNotNull(blog.getId()); // 验证主键是否自动生成
        System.out.println("新增博客成功，ID：" + blog.getId());
    }

    // 测试根据 ID 查询博客
    @Test
    public void testSelectBlogById() {
        System.out.println("\n===== 开始测试根据 ID 查询博客 =====");

        // 先新增一条数据（无参构造器 + setter）
        Blog blog = new Blog();
        blog.setTitle("Spring Boot 集成 MyBatis");
        blog.setContent("Spring Boot 与 MyBatis 的整合步骤...");
        blog.setAuthor("架构师");
        blogMapper.insert(blog);
        Long blogId = blog.getId(); // 获取新增后的 ID

        // 执行查询
        Blog queriedBlog = blogMapper.selectById(blogId);

        // 验证结果（使用 getter 取值）
        assertNotNull(queriedBlog);
        assertEquals("Spring Boot 集成 MyBatis", queriedBlog.getTitle());
        assertEquals("架构师", queriedBlog.getAuthor());
        System.out.println("查询成功，博客内容：" + queriedBlog.getContent());
    }

    // 测试查询所有博客
    @Test
    public void testSelectAllBlogs() {
        System.out.println("\n===== 开始测试查询所有博客 =====");

        // 先新增两条测试数据（无参构造器 + setter）
        Blog blog1 = new Blog();
        blog1.setTitle("Java 并发编程");
        blog1.setContent("深入理解线程池...");
        blog1.setAuthor("程序员A");
        blogMapper.insert(blog1);

        Blog blog2 = new Blog();
        blog2.setTitle("MySQL 优化技巧");
        blog2.setContent("索引设计与查询优化...");
        blog2.setAuthor("DBA");
        blogMapper.insert(blog2);

        // 执行查询所有
        List<Blog> blogList = blogMapper.selectAll();

        // 验证结果
        assertTrue(blogList.size() >= 2); // 至少有两条数据
        System.out.println("查询到 " + blogList.size() + " 条博客：");
        for (Blog b : blogList) {
            // 使用 getter 取值
            System.out.println("- [" + b.getId() + "] " + b.getTitle() + "（作者：" + b.getAuthor() + "）");
        }
    }

    // 测试更新博客
    @Test
    public void testUpdateBlog() {
        System.out.println("\n===== 开始测试更新博客 =====");

        // 先新增一条数据
        Blog blog = new Blog();
        blog.setTitle("原始标题");
        blog.setContent("原始内容");
        blog.setAuthor("作者A");
        blogMapper.insert(blog);
        Long blogId = blog.getId();

        // 构建更新对象（设置要更新的字段）
        Blog updateBlog = new Blog();
        updateBlog.setId(blogId); // 必须指定要更新的 ID
        updateBlog.setTitle("更新后的标题");
        updateBlog.setContent("这是修改后的博客内容，增加了更多细节...");

        // 执行更新
        int result = blogMapper.updateBySet(updateBlog);

        // 验证更新结果
        assertEquals(1, result);
        Blog updatedBlog = blogMapper.selectById(blogId);
        assertEquals("更新后的标题", updatedBlog.getTitle());
        assertEquals("这是修改后的博客内容，增加了更多细节...", updatedBlog.getContent());
        System.out.println("博客更新成功！");
    }

    // 测试删除博客
    @Test
    public void testDeleteBlog() {
        System.out.println("\n===== 开始测试删除博客 =====");

        // 先新增一条数据
        Blog blog = new Blog();
        blog.setTitle("待删除博客");
        blog.setContent("这篇博客将被删除...");
        blog.setAuthor("测试账号");
        blogMapper.insert(blog);
        Long blogId = blog.getId();

        // 执行删除
        int result = blogMapper.deleteById(blogId);

        // 验证删除结果
        assertEquals(1, result);
        Blog deletedBlog = blogMapper.selectById(blogId);
        assertNull(deletedBlog); // 删除后查询应为 null
        System.out.println("博客删除成功！");
    }

    // 释放资源（测试后执行）
    @After
    public void destroy() {
        if (session != null) {
            session.close(); // 关闭 SqlSession
        }
        System.out.println("\n===== 测试环境资源释放完成 =====");
    }
}