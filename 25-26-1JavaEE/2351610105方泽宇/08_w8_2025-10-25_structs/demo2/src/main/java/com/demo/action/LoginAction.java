package com.demo.action;

import com.opensymphony.xwork2.ActionSupport;

public class LoginAction extends ActionSupport {
    private String username;
    private String password;

    public String getUsername() {
        return username;
    }
    
    public void setUsername(String username) {
        this.username = username;
    }
    
    public String getPassword() {
        return password;
    }
    
    public void setPassword(String password) {
        this.password = password;
    }
    public String execute() {
        return SUCCESS;
    }
    public String login() {
        if ("admin".equals(username) && "password".equals(password)) {
            return SUCCESS;
        } else {
            addActionError("Invalid username or password!");
            return ERROR;
        }
    }
}