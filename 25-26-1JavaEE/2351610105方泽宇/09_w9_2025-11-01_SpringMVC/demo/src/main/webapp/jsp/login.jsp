<%--
  Created by IntelliJ IDEA.
  User: fang50253
  Date: 2025/10/31
  Time: 18:39
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Spring MVC Demo登录</title>
</head>
<body>
  <h3>Spring MVC Demo用户登录</h3>
  <form action="user.do" method="post">
    <table>
      <tr>
        <td>ID:</td>
        <td><input type="text" name="id"></td>
      </tr>
      <tr>
        <td>Name:</td>
        <td><input type="text" name="name"></td>
      </tr>
      <tr>
        <td>CardID:</td>
        <td><input type="text" name="cardID"></td>
      </tr>
      <tr>
        <td></td>
        <td><input type="submit" value="submit"></td>
        <td><input type="reset" value="reset"></td>
      </tr>
    </table>
  </form>
</body>
</html>