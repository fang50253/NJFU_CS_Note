package ssm.test;

import java.util.List;

public interface BlogMapper {
    // 新增博客
    int insert(Blog blog);

    // 根据ID查询
    Blog selectById(Long id);

    // 查询所有博客
    List<Blog> selectAll();

    // 动态更新（根据非空字段更新）
    int updateBySet(Blog blog);

    // 根据ID删除
    int deleteById(Long id);
}