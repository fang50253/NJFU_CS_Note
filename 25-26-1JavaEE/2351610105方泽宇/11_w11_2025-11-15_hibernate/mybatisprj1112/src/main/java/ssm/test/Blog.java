package ssm.test;

import java.time.LocalDateTime;

public class Blog {
    private Long id;
    private String title;
    private String content;
    private String author;
    private LocalDateTime publishTime;
    private LocalDateTime updateTime;
    private Integer readCount;
    private Integer status;

    // 无参构造
    public Blog() {}

    // 带参构造（用于新增）
    public Blog(String title, String content, String author) {
        this.title = title;
        this.content = content;
        this.author = author;
        this.publishTime = LocalDateTime.now();
        this.updateTime = LocalDateTime.now();
        this.readCount = 0;
        this.status = 1;
    }

    // Getter和Setter
    public Long getId() { return id; }
    public void setId(Long id) { this.id = id; }

    public String getTitle() { return title; }
    public void setTitle(String title) { this.title = title; }

    public String getContent() { return content; }
    public void setContent(String content) { this.content = content; }

    public String getAuthor() { return author; }
    public void setAuthor(String author) { this.author = author; }

    public LocalDateTime getPublishTime() { return publishTime; }
    public void setPublishTime(LocalDateTime publishTime) { this.publishTime = publishTime; }

    public LocalDateTime getUpdateTime() { return updateTime; }
    public void setUpdateTime(LocalDateTime updateTime) { this.updateTime = updateTime; }

    public Integer getReadCount() { return readCount; }
    public void setReadCount(Integer readCount) { this.readCount = readCount; }

    public Integer getStatus() { return status; }
    public void setStatus(Integer status) { this.status = status; }

    @Override
    public String toString() {
        return "Blog{" +
                "id=" + id +
                ", title='" + title + '\'' +
                ", author='" + author + '\'' +
                ", publishTime=" + publishTime +
                ", readCount=" + readCount +
                ", status=" + status +
                '}';
    }
}