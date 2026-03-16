<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="java.util.Date" %>
<html>
<head>
    <title>用户会话信息</title>
    <style>
        body { font-family: "微软雅黑"; padding: 20px; }
        .info-item { margin: 10px 0; font-size: 16px; }
    </style>
</head>
<body>
<h1>用户会话信息</h1>
<%
    // 确保session存在并处理访问计数
    if (request.getSession(false) == null) {
        request.getSession(true);
    }
    
    // 获取或初始化访问计数
    Integer visitCount = (Integer) session.getAttribute("visitCount");
    if (visitCount == null) {
        visitCount = 1;
    } else {
        visitCount++;
    }
    session.setAttribute("visitCount", visitCount);
%>
<div class="info-item">会话ID: <%= session.getId() %></div>
<div class="info-item">当前页面访问次数: <%= visitCount %></div>
<div class="info-item">当前时间: <%= new Date() %></div>
</body>
</html>