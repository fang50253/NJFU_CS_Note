<%--
  Created by IntelliJ IDEA.
  User: fang50253
  Date: 2025/10/17
  Time: 23:52
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>This is a shopcart!</title>
</head>
<body>
<form id="form1" name="form1" method="post" action="shop_do.jsp">
    <p><strong>请选择你要购买的商品</strong></p>
    <table width="300" border="1">
        <tr>
            <td>商品名：</td>
            <td><input type="text" name="goods"></td>
        </tr>
        <tr>
            <td colspan="2">
                <div align="center">
                    <input type="submit" name="Submit" value="加入购物车">
                    <input type="reset" name="Submit2" value="重选">
                </div>
            </td>
        </tr>
    </table>
</form>
</body>
</html>
