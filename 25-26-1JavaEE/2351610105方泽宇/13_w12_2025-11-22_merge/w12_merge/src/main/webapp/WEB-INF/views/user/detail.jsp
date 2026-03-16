<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<html>
<head>
    <title>用户详情</title>
    <style>
        .user-detail { max-width: 500px; margin: 20px auto; }
        .field { margin: 10px 0; }
        .label { font-weight: bold; width: 100px; display: inline-block; }
        .actions { margin-top: 20px; }
    </style>
</head>
<body>
<div class="user-detail">
    <h2>用户详情</h2>

    <div class="field">
        <span class="label">用户ID：</span>
        <span>${user.id}</span>
    </div>

    <div class="field">
        <span class="label">用户名：</span>
        <span>${user.username}</span>
    </div>

    <div class="field">
        <span class="label">邮箱：</span>
        <span>${user.email}</span>
    </div>

    <div class="field">
        <span class="label">年龄：</span>
        <span>${user.age}</span>
    </div>

    <div class="field">
        <span class="label">创建时间：</span>
        <span><fmt:formatDate value="${user.createTime}" pattern="yyyy-MM-dd HH:mm:ss"/></span>
    </div>

    <div class="actions">
        <button onclick="location.href='${pageContext.request.contextPath}/user/edit/${user.id}'">编辑</button>
        <button onclick="location.href='${pageContext.request.contextPath}/user/list'">返回列表</button>
    </div>
</div>
</body>
</html>