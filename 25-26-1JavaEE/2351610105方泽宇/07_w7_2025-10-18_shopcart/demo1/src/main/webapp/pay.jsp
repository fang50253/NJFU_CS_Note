<%@ page import="java.util.ArrayList" %><%--
  Created by IntelliJ IDEA.
  User: fang50253
  Date: 2025/10/17
  Time: 23:59
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Pay.jsp</title>
</head>
<body>
非常感谢您的光临！您本次在我们这里购买了一下商品：<br>
<%
  ArrayList list = (ArrayList)session.getAttribute("list");
  for(int i=0;i<list.size();i++){
    String goodsName = (String)list.get(i);
%>
商品：<%=i %>:<%=goodsName %><br>
<%} %>
</body>
</html>
