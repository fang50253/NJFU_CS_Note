<%--
  Created by IntelliJ IDEA.
  User: Administrator
  Date: 2022/11/15 0015
  Time: 14:55
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<html>
<script language="javascript"> /** * 批量提交方法 */
function deleteMuch() {
    console.log("deleteMuch");
    var str=document.getElementsByName("id");
    var objarray=str.length;
    var chestr="";
    for (i=0;i<objarray;i++) {
        if(str[i].checked == true) {
            chestr+=str[i].value+",";
        }
    }
    if(chestr.length>0){
        document.forms[0].action = "${pageContext.request.contextPath}/user/deleteMuch";
        document.forms[0].submit(); <!-- 手动提交 -->
    }else {
        alert("请选择删除记录");
    }
}
</script>
<head>
    <title>Title</title>
</head>
<body>
<form method="post">
    <div style="padding:20px;"> 书籍列表 </div>
    <div style="padding-left:40px;padding-bottom: 10px;">
        <a href="${pageContext.request.contextPath}/user/toCreatUser">新增</a>
        <!-- 跳转路径 --> <a href="#" onclick="deleteMuch()">批量删除</a>
        <!-- 调用 JavaScript --> </div> <table border="1"> <tr> <td>选择</td> <td>编号</td> <td>isbn</td> <td>书名</td> <td>作者</td> <td>操作</td> </tr>
    <c:forEach items="${userlist}" var="p">
        <tr> <td> <input type="checkbox" name="id" value="${p.id}"/> </td> <td>${p.id}</td> <td>${p.isbn}</td> <td>${p.username}</td> <td>${p.author}</td><td> <a href=toUpdateUserInfo?id=${p.id}>修改</a> <a href=deleteById?id=${p.id}>删除</a> </td> </tr>
    </c:forEach> </table> </form>
</body>
</html>