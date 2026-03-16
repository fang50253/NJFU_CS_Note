<!-- src/main/webapp/WEB-INF/views/user/form.jsp -->
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head>
    <title>
        <c:choose>
            <c:when test="${not empty user.id}">编辑用户</c:when>
            <c:otherwise>添加用户</c:otherwise>
        </c:choose>
    </title>
    <style>
        .user-form { max-width: 400px; margin: 20px auto; }
        .form-group { margin: 10px 0; }
        label { display: inline-block; width: 80px; }
        input[type="text"], input[type="number"] { width: 200px; padding: 5px; }
        .actions { margin-top: 20px; }
        .error { color: red; font-size: 12px; }
    </style>
</head>
<body>
<div class="user-form">
    <h2>
        <c:choose>
            <c:when test="${not empty user.id}">编辑用户</c:when>
            <c:otherwise>添加用户</c:otherwise>
        </c:choose>
    </h2>

    <form action="${pageContext.request.contextPath}/user/save" method="post">
        <c:if test="${not empty user.id}">
            <input type="hidden" name="id" value="${user.id}">
        </c:if>

        <div class="form-group">
            <label for="username">用户名：</label>
            <input type="text" id="username" name="username"
                   value="${user.username}" required>
        </div>

        <div class="form-group">
            <label for="email">邮箱：</label>
            <input type="text" id="email" name="email"
                   value="${user.email}">
        </div>

        <div class="form-group">
            <label for="age">年龄：</label>
            <input type="number" id="age" name="age"
                   value="${user.age}" min="1" max="150">
        </div>

        <div class="actions">
            <button type="submit">保存</button>
            <button type="button" onclick="location.href='${pageContext.request.contextPath}/user/list'">取消</button>
        </div>
    </form>
</div>
</body>
</html>