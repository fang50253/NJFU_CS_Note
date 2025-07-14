//1.导入http模块
var http = require('http');

//2.创建实例
var server = http.createServer();

//3.监听request请求时间，设置请求处理函数
server.on('request', function (req, res) {
    console.log('收到请求了，请求路径是：' + req.url);
    res.end('hello world');
})

//4.启动服务
server.listen(3000, function () {
    console.log('服务器启动成功，请访问：http://127.0.0.1:3000');
})