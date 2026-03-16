package ssm.test;

import org.apache.ibatis.annotations.Param;
import java.util.List;

public interface BlogMapper {
    // 新增博客
    int insert(Blog blog);

    // 根据ID删除
    int deleteById(Long id);

    // 动态更新（只更新非空字段）
    int update(Blog blog);

    // 根据ID查询
    Blog selectById(Long id);

    // 查询所有博客
    List<Blog> selectAll();

    // 条件查询（标题模糊匹配+作者精确匹配）
    List<Blog> selectByCondition(@Param("title") String title, @Param("author") String author);

    // 批量删除
    int batchDelete(@Param("ids") List<Long> ids);
}