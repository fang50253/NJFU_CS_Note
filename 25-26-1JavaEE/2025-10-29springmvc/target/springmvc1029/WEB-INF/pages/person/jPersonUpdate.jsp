<%@ page contentType="text/html;charset=UTF-8" language="java" isELIgnored="false" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core"   prefix="c" %>
<html>
<head>
    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <title>PersonList</title>
</head>
<body>
<form action="${pageContext.request.contextPath}/person/updatePersonList.action" method="post">
 
    <input type="hidden" name="id" value="${p.id}"/>

    <div style="padding:20px;">
    修改人员信息
    </div>

    <table>
        <tr>
            <td>>姓名:</td>
            <td><input type="text" name="name" value="${p.name}"/></td>
        </tr>
        <tr>
            <td>年龄:</td>
            <td><input type="text" name="age" value="${p.age}"/></td>
        </tr>
        <tr>
            <td colspan="2"><input type="submit" name="btnOK" value="保存"/></td>
        </tr>
    </table>
</form>

</body>
</html>