// 导入http模块
var http = require('http');

// 创建服务器实例
var server = http.createServer();

// 监听request请求事件，设置请求处理函数
server.on('request', function(request, response) {
    // 1. 获取请求的url地址
    var url = request.url;
    console.log('收到请求了，请求路径是：' + url);

    // 2. 设置默认的响应内容是404 Not Found
    var content = '404 Not Found';

    // 3. 判断用户请求是否为/或者/index.html，显示首页
    if (url === '/' || url === '/index.html') {
        content = '首页';
    }
    // 4. 判断用户请求是否为/about.html，页面显示关于页面
    else if (url === '/about.html') {
        content = '关于页面';
    }

    // 5. 设置content type响应头，防止中文乱码
    response.setHeader('Content-Type', 'text/html; charset=utf-8');

    // 6. 使用res.end()把内容响应给客户端
    response.end(content);
});

// 启动服务
server.listen(3000, function() {
    console.log('服务器启动成功，请访问：http://127.0.0.1:3000');
});