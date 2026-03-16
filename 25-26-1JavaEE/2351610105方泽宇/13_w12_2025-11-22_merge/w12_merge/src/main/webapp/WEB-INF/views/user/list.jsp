<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head>
    <title>用户列表</title>
    <script>
        // 全选/全不选
        function selectAll() {
            var checkboxes = document.getElementsByName('userIds');
            var selectAll = document.getElementById('selectAll').checked;
            for (var i = 0; i < checkboxes.length; i++) {
                checkboxes[i].checked = selectAll;
            }
        }

        // 批量删除确认
        function confirmBatchDelete() {
            var checkboxes = document.getElementsByName('userIds');
            var selected = false;
            for (var i = 0; i < checkboxes.length; i++) {
                if (checkboxes[i].checked) {
                    selected = true;
                    break;
                }
            }

            if (!selected) {
                alert('请至少选择一个用户！');
                return false;
            }

            return confirm('确定要删除选中的用户吗？');
        }

        // 单个删除确认
        function confirmDelete(username) {
            return confirm('确定要删除用户 \"' + username + '\" 吗？');
        }
    </script>
    <style>
        table { width: 100%; border-collapse: collapse; margin-top: 10px; }
        th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }
        th { background-color: #f2f2f2; }
        .actions { white-space: nowrap; }
        .batch-actions { margin: 10px 0; }
    </style>
</head>
<body>
<h2>用户管理</h2>

<div class="batch-actions">
    <form action="${pageContext.request.contextPath}/user/batchDelete" method="post" onsubmit="return confirmBatchDelete()">
        <button type="button" onclick="location.href='${pageContext.request.contextPath}/user/add'">添加用户</button>
        <button type="submit">批量删除</button>
    </form>
</div>

<table>
    <thead>
    <tr>
        <th width="30">
            <input type="checkbox" id="selectAll" onclick="selectAll()">
        </th>
        <th>ID</th>
        <th>用户名</th>
        <th>邮箱</th>
        <th>年龄</th>
        <th>创建时间</th>
        <th>操作</th>
    </tr>
    </thead>
    <tbody>
    <c:forEach items="${users}" var="user">
        <tr>
            <td><input type="checkbox" name="userIds" value="${user.id}"></td>
            <td>${user.id}</td>
            <td>${user.username}</td>
            <td>${user.email}</td>
            <td>${user.age}</td>
            <td>${user.createTime}</td>
            <td class="actions">
                <a href="${pageContext.request.contextPath}/user/detail/${user.id}">查看</a> |
                <a href="${pageContext.request.contextPath}/user/edit/${user.id}">编辑</a> |
                <form action="${pageContext.request.contextPath}/user/delete/${user.id}" method="post"
                      style="display:inline;"
                      onsubmit="return confirmDelete('${user.username}')">
                    <button type="submit">删除</button>
                </form>
            </td>
        </tr>
    </c:forEach>
    <c:if test="${empty users}">
        <tr>
            <td colspan="7" style="text-align: center;">暂无用户数据</td>
        </tr>
    </c:if>
    </tbody>
</table>
</body>
</html>