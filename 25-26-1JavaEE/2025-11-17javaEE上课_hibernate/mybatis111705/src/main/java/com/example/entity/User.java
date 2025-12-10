package com.example.entity;

public class User {
    private Long id;
    private String name;
    private String email;

    // 构造器、getter、setter
    public User() {}

    public User(String name, String email) {
        this.name = name;
        this.email = email;
    }

    // getter 和 setter 方法
    public Long getId() { return id; }
    public void setId(Long id) { this.id = id; }

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }

    public String getEmail() { return email; }
    public void setEmail(String email) { this.email = email; }

    @Override
    public String toString() {
        return "User{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", email='" + email + '\'' +
                '}';
    }
}
