# 第三章 文字与段落

## 3.1 基本的文字排版

段落 `<p></p>` *会存在自动换行

标题 `<h1> </h1>` *一共会有6级，相对来说`<h1>`是最大`<h6>`最小

换行符 `<br/>` *这是一个单标签，只需要在每一个需要换行的位置加上即可

预先格式化 `<pre></pre>` *保留空格和换行符，原样输出里面的内容

水平线 `<hr/>` 也是单标签

强调文本 `<b> <i> <em> <strong>`，一般`<b> <strong>`表示粗体，`<i> <em>`表示斜体，`<em>`表示有压力的强调

作品标签 `<cite>` *书籍、课程名称

小型文本 `<small>` *免责声明、注意事项、版权声明(旁注)

标记文本 `<ins>`(插入)   `<del>`(删除)   `<sup>`(上标)   `<sub>`(下表)

```html
x<sup>2</sup>+2x-3=0
```

旁注 `<ruby> <rt> <rp>` 部分浏览器不支持ruby标签，不会正常显示注音

日期时间`<time>`

```html
<time datetime="" pubdate="">元素内容</time>
```
* pubdate表示发布时间，datetime是正常的时间

无语意的容器元素： `<div>`和`<span>`

特殊符号

| Column 1  | Column 2  | Column 3  |
|:----------|:----------|:----------|
| ©️    | &copy    | 版权符号    |
|      | &nbsp    | 空格    |
| <    | &lt    | 左尖括号    |
| >    | &gt    | 右尖括号    |



注释
```
<!--这是注释-->
```

## 3.2 描述文本的语意化，结构化元素

## 3.3 块级元素和行内元素

## 3.4 无语义的容器元素

## 3.5 

# 第四章 图像、音频和视频

## 4.1文件路径

- 文件路径是文件在电脑中的位置，表示路径的方式有两种，相对路径和绝对路径

- 绝对路径

“https://www.sina.com.cn/index.html/"

"ftp://222.22.49.183"

- 相对路径

引用同一目录下的文件`"logout.html"`

引用子目录下的文件`admin/logout.html`

引用上一级的文件`../logou.html`

## 4.2图像

`<img src="url" alt="替代文本/> width="像素|百分比" height="像素|百分比"`   src是source，来源；alt表示图片加载失败显示的内容

常见格式：jpeg，gif和png

## 4.3视频

`<video src="url" controls="controls" autoplay="autoplay" width="百分比|像素" height="百分比|像素" preload="auto|meta|none" loop="loop">`

常见格式：mp4,webm,ogg

多种源的语法

```html
<video>
    <source src="*.mp4">
    <source src="*.webm">
    浏览器不支持video元素
</video>
```
## 4.4音频

`<audio src="url" controls="controls" autoplay="autoplay" width="百分比|像素" height="百分比|像素" preload="auto|meta|none" loop="loop">`

常见格式：mp3,ogg audios,aac

# 第五章 超链接

## 5.1