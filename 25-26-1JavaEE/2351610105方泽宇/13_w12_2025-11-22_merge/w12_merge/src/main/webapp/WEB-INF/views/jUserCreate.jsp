<%--
  Created by IntelliJ IDEA.
  User: Administrator
  Date: 2022/11/15 0015
  Time: 15:07
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core"   prefix="c" %>
<html>
<head>
    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <title>PersonList</title>
</head>
<body>
<form action="${pageContext.request.contextPath}/user/updateUser" method="post">



    <div style="padding:20px;">
        增加书籍信息
    </div>
    <input type="hidden" name="id" value="${p.id}"/>
    <table>
        <tr>
            <td>书名:</td>
            <td><input type="text" name="username" value="${p.username}" /></td>
        </tr>
        <tr>
            <td>ISBN:</td>
            <td><input type="text" name="isbn" value="${p.isbn}" /></td>
        </tr>
        <tr>
            <td>作者:</td>
            <td><input type="text" name="author" value="${p.author}" /></td>
        </tr>
        <tr>
            <td colspan="2"><input type="submit" name="btnOK" value="保存"/></td>
        </tr>
    </table>
</form>

</body>
</html>