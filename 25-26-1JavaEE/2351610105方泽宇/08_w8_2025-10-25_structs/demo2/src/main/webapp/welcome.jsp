<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="s" uri="/struts-tags" %>
<html>
<head>
    <title>Welcome</title>
</head>
<body>
    <h2>Login Successful</h2>
    <p>Welcome, <s:property value="username"/>!</p>
    <a href="login.action">Logout</a>
</body>
</html>