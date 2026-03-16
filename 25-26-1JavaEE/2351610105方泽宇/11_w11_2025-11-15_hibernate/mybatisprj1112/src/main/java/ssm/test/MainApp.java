package ssm.test;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.*;

public class MainApp {
    private static SqlSessionFactory sqlSessionFactory;

    static {
        try {
            String resource = "conf.xml";
            sqlSessionFactory = new SqlSessionFactoryBuilder().build(Resources.getResourceAsReader(resource));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // 测试各种动态SQL功能
        testInsert();
        testSelectByCondition();
        testSelectByChoose();
        testSelectByWhere();
        testUpdateBySet();
        testSelectByTrim();
        testForeachOperations();
        testBind();
        testComplexCondition();
        testPriceRange();
        testCountByCategory();
    }

    private static void testInsert() {
        try (SqlSession session = sqlSessionFactory.openSession()) {
            BookMapper mapper = session.getMapper(BookMapper.class);

            Book book = new Book("深入理解Java虚拟机", "周志明", "9787111421900",
                    new BigDecimal("99.00"), "编程", "机械工业出版社",
                    LocalDate.of(2013,9,01), 40);
            mapper.insert(book);
            session.commit();
            System.out.println("插入书籍成功，ID: " + book.getId());
        }
    }

    private static void testSelectByCondition() {
        try (SqlSession session = sqlSessionFactory.openSession()) {
            BookMapper mapper = session.getMapper(BookMapper.class);

            Book condition = new Book();
            condition.setTitle("Java");
            condition.setCategory("编程");

            List<Book> books = mapper.selectByCondition(condition);
            System.out.println("=== 条件查询结果 ===");
            books.forEach(System.out::println);
        }
    }

    private static void testSelectByChoose() {
        try (SqlSession session = sqlSessionFactory.openSession()) {
            BookMapper mapper = session.getMapper(BookMapper.class);

            Book condition = new Book();
            // condition.setTitle("Spring"); // 注释掉测试otherwise
            List<Book> books = mapper.selectByChoose(condition);
            System.out.println("=== Choose查询结果 ===");
            books.forEach(System.out::println);
        }
    }

    private static void testSelectByWhere() {
        try (SqlSession session = sqlSessionFactory.openSession()) {
            BookMapper mapper = session.getMapper(BookMapper.class);

            Book condition = new Book();
            condition.setAuthor("机械工业");
            condition.setStatus(1);

            List<Book> books = mapper.selectByWhere(condition);
            System.out.println("=== Where查询结果 ===");
            books.forEach(System.out::println);
        }
    }

    private static void testUpdateBySet() {
        try (SqlSession session = sqlSessionFactory.openSession()) {
            BookMapper mapper = session.getMapper(BookMapper.class);

            Book book = new Book();
            book.setId(1L);
            book.setPrice(new BigDecimal("115.00"));
            book.setStockQuantity(45);

            int result = mapper.updateBySet(book);
            session.commit();
            System.out.println("动态更新影响行数: " + result);
        }
    }

    private static void testSelectByTrim() {
        try (SqlSession session = sqlSessionFactory.openSession()) {
            BookMapper mapper = session.getMapper(BookMapper.class);

            Book condition = new Book();
            condition.setPublisher("人民邮电出版社");

            List<Book> books = mapper.selectByTrim(condition);
            System.out.println("=== Trim查询结果 ===");
            books.forEach(System.out::println);
        }
    }

    private static void testForeachOperations() {
        try (SqlSession session = sqlSessionFactory.openSession()) {
            BookMapper mapper = session.getMapper(BookMapper.class);

            // 批量查询
            List<Long> ids = Arrays.asList(1L, 2L, 3L);
            List<Book> books = mapper.selectByIds(ids);
            System.out.println("=== 批量查询结果 ===");
            books.forEach(System.out::println);

            // 批量更新价格
            mapper.batchUpdatePrice(ids, new BigDecimal("88.00"));
            session.commit();
            System.out.println("批量更新价格完成");
        }
    }

    private static void testBind() {
        try (SqlSession session = sqlSessionFactory.openSession()) {
            BookMapper mapper = session.getMapper(BookMapper.class);

            List<Book> books = mapper.selectByTitleLike("实战");
            System.out.println("=== Bind查询结果 ===");
            books.forEach(System.out::println);
        }
    }

    private static void testComplexCondition() {
        try (SqlSession session = sqlSessionFactory.openSession()) {
            BookMapper mapper = session.getMapper(BookMapper.class);

            Map<String, Object> params = new HashMap<>();
            params.put("status", 1);
            params.put("categories", Arrays.asList("编程", "数据库"));
            params.put("minPrice", new BigDecimal("50.00"));
            params.put("maxPrice", new BigDecimal("100.00"));
            params.put("minStock", 10);
            params.put("orderBy", "price DESC");

            List<Book> books = mapper.selectByComplexCondition(params);
            System.out.println("=== 复杂条件查询结果 ===");
            books.forEach(System.out::println);
        }
    }

    private static void testPriceRange() {
        try (SqlSession session = sqlSessionFactory.openSession()) {
            BookMapper mapper = session.getMapper(BookMapper.class);

            List<Book> books = mapper.selectByPriceRange(new BigDecimal("80.00"), new BigDecimal("120.00"));
            System.out.println("=== 价格范围查询结果 ===");
            books.forEach(System.out::println);
        }
    }

    private static void testCountByCategory() {
        try (SqlSession session = sqlSessionFactory.openSession()) {
            BookMapper mapper = session.getMapper(BookMapper.class);

            List<Map<String, Object>> stats = mapper.countByCategory();
            System.out.println("=== 分类统计结果 ===");
            stats.forEach(stat -> {
                System.out.println("分类: " + stat.get("category") +
                        ", 数量: " + stat.get("count") +
                        ", 平均价格: " + stat.get("avg_price"));
            });
        }
    }
}