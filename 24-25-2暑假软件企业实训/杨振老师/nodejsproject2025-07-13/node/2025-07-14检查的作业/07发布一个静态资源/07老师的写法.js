//1.导入http模块
var http = require('http');
// 导入fs模块
var fs = require('fs');
// 导入path模块（新增）
var path = require('path');

//2.创建实例
var server = http.createServer();

//3.监听request请求时间，设置请求处理函数
server.on('request', function (req, res) {
    //访问/，展示index.html
    if (req.url === '/') {
        req.url = '/index.html';
    }
    
    // 构建完整文件路径（修改）
    var filePath = path.join(__dirname, 'clock', req.url);
    
    //读取clock目录下的文件（修改路径）
    fs.readFile(filePath, function(err, data) {
        if(err) {
            return res.end('404 Not Found');
        }
        res.end(data);
    })
})

//4.启动服务
server.listen(3000, function () {
    console.log('服务器启动成功，请访问：http://127.0.0.1:3000');
})