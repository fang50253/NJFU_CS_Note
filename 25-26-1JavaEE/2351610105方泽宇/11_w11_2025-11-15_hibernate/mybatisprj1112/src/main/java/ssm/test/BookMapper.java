package ssm.test;

import org.apache.ibatis.annotations.Param;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.List;
import java.util.Map;

public interface BookMapper {

    // 1. 插入书籍
    int insert(Book book);

    // 2. if 标签 - 条件查询
    List<Book> selectByCondition(Book book);

    // 3. choose/when/otherwise 标签 - 多条件选择
    List<Book> selectByChoose(Book book);

    // 4. where 标签 - 自动处理WHERE条件
    List<Book> selectByWhere(Book book);

    // 5. set 标签 - 动态更新
    int updateBySet(Book book);

    // 6. trim 标签 - 自定义前缀后缀
    List<Book> selectByTrim(Book book);
    int updateByTrim(Book book);

    // 7. foreach 标签 - 批量操作
    List<Book> selectByIds(@Param("ids") List<Long> ids);
    int batchInsert(@Param("books") List<Book> books);
    int batchDelete(@Param("ids") List<Long> ids);
    int batchUpdatePrice(@Param("ids") List<Long> ids, @Param("price") BigDecimal price);

    // 8. bind 标签 - 创建变量
    List<Book> selectByTitleLike(@Param("title") String title);

    // 9. 复杂条件查询
    List<Book> selectByComplexCondition(Map<String, Object> params);

    // 10. 价格范围查询
    List<Book> selectByPriceRange(@Param("minPrice") BigDecimal minPrice,
                                  @Param("maxPrice") BigDecimal maxPrice);

    // 11. 分类统计
    List<Map<String, Object>> countByCategory();

    // 12. 根据ID查询
    Book selectById(Long id);

    // 13. 删除书籍
    int deleteById(Long id);

    // 14. 更新库存
    int updateStock(@Param("id") Long id, @Param("quantity") Integer quantity);
}