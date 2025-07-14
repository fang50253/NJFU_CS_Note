# HTML & CSS 考试准备资料

## 常见HTML标记

### 基本结构标记
```html
<!DOCTYPE html>
<html>
<head>
    <title>页面标题</title>
    <meta charset="UTF-8">
    <link rel="stylesheet" href="styles.css">
    <style>内部样式</style>
</head>
<body>
    <!-- 页面内容 -->
</body>
</html>
```

### 文本标记
- `<h1>`到`<h6>`: 标题
- `<p>`: 段落
- `<br>`: 换行
- `<hr>`: 水平线
- `<strong>`或`<b>`: 加粗
- `<em>`或`<i>`: 斜体
- `<span>`: 行内容器

### 列表标记
- `<ul>`: 无序列表
- `<ol>`: 有序列表
- `<li>`: 列表项
- `<dl>`: 定义列表
- `<dt>`: 定义术语
- `<dd>`: 定义描述

### 链接和图片
- `<a href="url">链接文本</a>`
- `<img src="image.jpg" alt="描述">`

### 表格标记
```html
<table>
    <tr>
        <th>表头</th>
        <th>表头</th>
    </tr>
    <tr>
        <td>数据</td>
        <td>数据</td>
    </tr>
</table>
```

### 表单标记
```html
<form action="submit.php" method="post">
    <input type="text" name="username">
    <input type="password" name="pwd">
    <input type="radio" name="gender" value="male">
    <input type="checkbox" name="hobby" value="reading">
    <select name="country">
        <option value="cn">中国</option>
    </select>
    <textarea name="comments"></textarea>
    <button type="submit">提交</button>
</form>
```

### 语义化标记
- `<header>`: 页眉
- `<nav>`: 导航
- `<main>`: 主要内容
- `<article>`: 文章
- `<section>`: 区域
- `<aside>`: 侧边栏
- `<footer>`: 页脚

## 重要考点

### HTML部分
1. 文档基本结构
2. 常用标签及其属性
3. 表格和表单的使用
4. 语义化HTML5标签
5. 图片和链接的使用
6. 列表的使用
7. 特殊字符的表示(如`&nbsp;`)

### CSS部分
1. CSS选择器(元素、类、ID、后代、子元素、伪类等)
2. 盒模型(margin、border、padding、content)
3. 定位(position: static/relative/absolute/fixed)
4. 浮动(float)和清除浮动(clear)
5. 常用样式属性(color、font、background等)
6. 布局技术(display: block/inline/inline-block/flex/grid)
7. 媒体查询(@media)响应式设计
8. 优先级和继承规则

## 模拟试卷

## 一、单项选择题 (每题1分，共20分)

1. 构成Web站点的最基本的单位是（ ）  
   A.网站 B.主页 C.网页 D.文字

2. HTML文档的根标签是（ ）  
   A.`<head>` B.`<body>` C.`<html>` D.`<root>`

3. 用于创建段落的HTML标签是（ ）  
   A.`<p>` B.`<para>` C.`<paragraph>` D.`<text>`

4. 在HTML中，用于创建超链接的标签是（ ）  
   A.`<a>` B.`<link>` C.`<href>` D.`<url>`

5. 用于插入图片的HTML标签是（ ）  
   A.`<img>` B.`<image>` C.`<picture>` D.`<photo>`

6. 定义表格行的HTML标签是（ ）  
   A.`<td>` B.`<tr>` C.`<th>` D.`<table-row>`

7. 定义表格单元格的HTML标签是（ ）  
   A.`<td>` B.`<tr>` C.`<th>` D.`<cell>`

8. 用于创建无序列表的HTML标签是（ ）  
   A.`<ol>` B.`<ul>` C.`<li>` D.`<list>`

9. 用于创建有序列表的HTML标签是（ ）  
   A.`<ol>` B.`<ul>` C.`<li>` D.`<list>`

10. 在HTML中，用于定义文档头部的标签是（ ）  
    A.`<header>` B.`<head>` C.`<title>` D.`<meta>`

11. 用于定义HTML文档标题的标签是（ ）  
    A.`<h1>` B.`<title>` C.`<header>` D.`<head>`

12. 用于创建表单的HTML标签是（ ）  
    A.`<input>` B.`<form>` C.`<submit>` D.`<fieldset>`

13. 用于创建文本输入框的HTML标签是（ ）  
    A.`<input type="button">` B.`<input type="text">`  
    C.`<text>` D.`<textbox>`

14. 用于创建提交按钮的HTML标签是（ ）  
    A.`<button>` B.`<input type="submit">`  
    C.`<submit>` D.`<input type="button">`

15. 用于定义CSS样式的HTML标签是（ ）  
    A.`<css>` B.`<style>` C.`<link>` D.`<script>`

16. 用于链接外部CSS文件的HTML标签是（ ）  
    A.`<css>` B.`<style>` C.`<link>` D.`<script>`

17. 在CSS中，用于设置文本颜色的属性是（ ）  
    A.`font-color` B.`text-color` C.`color` D.`font-style`

18. 在CSS中，用于设置背景颜色的属性是（ ）  
    A.`background-color` B.`bgcolor`  
    C.`color-background` D.`background`

19. 在CSS中，用于设置字体大小的属性是（ ）  
    A.`text-size` B.`font-size` C.`size` D.`font`

20. 在HTML中，用于添加注释的语法是（ ）  
    A.`<!-- 注释 -->` B.`// 注释`  
    C.`/* 注释 */` D.`<comment>注释</comment>`

## 二、简答题 (每题5分，共30分)

21. 什么是超链接？它对网站的作用是什么？

22. 简要说明HTML中`<div>`和`<span>`标签的区别。

23. 列举HTML中三种常见的列表类型，并简要说明它们的用途。

24. 什么是CSS？它在网页设计中的作用是什么？

25. 简要说明HTML表单的作用，并列举三种常见的表单元素。

26. 解释HTML中`<img>`标签的`src`属性和`alt`属性的作用。

## 三、程序阅读题 (每题5分，共30分)

27. 以下是表格代码，请解释该代码的功能：
```html
<table border="1">
  <tr>
    <th>商品名称</th>
    <th>价格</th>
    <th>库存</th>
  </tr>
  <tr>
    <td>手机</td>
    <td>2999</td>
    <td>50</td>
  </tr>
  <tr>
    <td>电脑</td>
    <td>5999</td>
    <td>20</td>
  </tr>
</table>
```

28. 阅读以下HTML代码，说明其功能：
```html
<!DOCTYPE html>
<html>
<head>
  <title>我的网页</title>
</head>
<body>
  <h1>欢迎来到我的网站</h1>
  <p>这是一个简单的网页示例。</p>
  <a href="https://www.example.com">点击这里访问示例网站</a>
</body>
</html>
```

29. 阅读以下CSS代码，说明其功能：
```css
body {
  font-family: Arial, sans-serif;
  background-color: #f0f0f0;
  margin: 0;
  padding: 20px;
}

h1 {
  color: blue;
  text-align: center;
}
```

30. 阅读以下HTML表单代码，说明其功能：
```html
<form action="/submit" method="post">
  <label for="username">用户名:</label>
  <input type="text" id="username" name="username"><br>
  
  <label for="password">密码:</label>
  <input type="password" id="password" name="password"><br>
  
  <input type="submit" value="登录">
</form>
```

31. 阅读以下HTML列表代码，说明其功能：
```html
<ul>
  <li>首页</li>
  <li>产品介绍</li>
  <li>关于我们</li>
  <li>联系方式</li>
</ul>
```

32. 阅读以下HTML代码，说明其功能：
```html
<!DOCTYPE html>
<html>
<head>
  <style>
    .highlight {
      background-color: yellow;
      font-weight: bold;
    }
  </style>
</head>
<body>
  <p>这是一段<span class="highlight">重要</span>的文字。</p>
</body>
</html>
```

## 四、程序填空题 (每空1分，共20分)

33. 下图为一个简单的表单，要求姓名和电话为必填项，请完成以下代码：
```html
<!DOCTYPE html>
<html>
<head>
  <title>必填项</title>
</head>
<body>
  <form>
    *姓名：<input type="(1)" name="name" (2)="required" /><br><br>
    *电话：<input type="(3)" name="phone" (2)="required" /><br><br>
    地&nbsp;址：<input type="(4)" name="address" /><br><br>
    <input type="(5)" (6)="提交" />
  </form>
</body>
</html>
```

34. 补全以下HTML代码，创建一个包含标题、段落和图片的简单网页：
```html
<!DOCTYPE (7)>
<html>
(8)
  <title>我的网页</title>
</(8)>
(9)
  <(10)>欢迎来到我的网站</(10)>
  <(11)>这是一个简单的网页示例。</(11)>
  <(12) src="example.jpg" (13)="示例图片">
</(9)>
</html>
```

35. 补全以下CSS代码，设置页面样式：
```html
<style>
  body {
    font-family: (14);
    background-(15): #f0f0f0;
  }
  h1 {
    (16): center;
    color: (17);
  }
  p {
    font-(18): 16px;
    line-(19): 1.5;
  }
</(20)>
```
