<%@ page import="java.util.ArrayList" %><%--
  Created by IntelliJ IDEA.
  User: fang50253
  Date: 2025/10/17
  Time: 23:57
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Shop_do.jsp</title>
</head>
<body>
<%
    String goodsName = request.getParameter("goods");//获取商品名称
    if(!goodsName.equals("")){
        goodsName = new String(goodsName.getBytes("ISO-8859-1"),"UTF-8");  //解决中文乱码问题
        ArrayList list = null;  //定义保存商品的动态数组
        list = (ArrayList)session.getAttribute("list");  //通过list属性取得购物车
        if(list==null){
            list = new ArrayList();
            list.add(goodsName);
            session.setAttribute("list", list);
        }else{
            list.add(goodsName);
        }
%>
<%
    }else{
        response.sendRedirect("shop.jsp");
    }
%>
<center>
    <strong>提示：您刚才选择了商品
        <font color="red"><%=goodsName %></font>
        ，请问您还想做什么？
    </strong><br><br>
    <button onclick="location.href='shopcart.jsp'">继续购买商品</button>
    <button onclick="location.href='pay.jsp'">到收银台结账</button>
</center>
</body>
</html>
