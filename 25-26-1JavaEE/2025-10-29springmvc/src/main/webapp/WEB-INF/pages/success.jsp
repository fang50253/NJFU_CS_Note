<%@ page language="java" contentType="text/html; charset=UTF-8"
         pageEncoding="UTF-8"  isELIgnored="false" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>sign  springmvc应用成功</title>
</head>
<body>
${message }
成功登陆名单
<c:forEach items="${studentlist}" var="p">
    <tr> <td> <input type="checkbox" name="id" value="${p.id}"/> </td> <td>学号${p.id}</td> <td> 姓名${p.name}</td>   </tr>
</c:forEach> </table>
</body>
</html>
