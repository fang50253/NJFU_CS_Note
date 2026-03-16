package ssm.test;

import java.time.LocalDateTime;

public class Blog {
    private Long id;
    private String title;       // 博客标题
    private String content;     // 博客内容
    private String author;      // 作者
    private LocalDateTime createTime;  // 创建时间
    private LocalDateTime updateTime;  // 更新时间

    // 1. 无参构造器（必须有，MyBatis 会通过反射实例化）
    public Blog() {}

    // 2. 全参构造器（可选，方便测试手动创建对象）
    public Blog(Long id, String title, String content, String author, LocalDateTime createTime, LocalDateTime updateTime) {
        this.id = id;
        this.title = title;
        this.content = content;
        this.author = author;
        this.createTime = createTime;
        this.updateTime = updateTime;
    }

    // 3. 所有字段的 Getter 方法（用于取值）
    public Long getId() { return id; }
    public String getTitle() { return title; }
    public String getContent() { return content; }
    public String getAuthor() { return author; }
    public LocalDateTime getCreateTime() { return createTime; }
    public LocalDateTime getUpdateTime() { return updateTime; }

    // 4. 所有字段的 Setter 方法（用于赋值）
    public void setId(Long id) { this.id = id; }
    public void setTitle(String title) { this.title = title; }
    public void setContent(String content) { this.content = content; }
    public void setAuthor(String author) { this.author = author; }
    public void setCreateTime(LocalDateTime createTime) { this.createTime = createTime; }
    public void setUpdateTime(LocalDateTime updateTime) { this.updateTime = updateTime; }

    // 可选：toString() 方法（方便打印对象信息）
    @Override
    public String toString() {
        return "Blog{" +
                "id=" + id +
                ", title='" + title + '\'' +
                ", author='" + author + '\'' +
                ", createTime=" + createTime +
                '}';
    }
}