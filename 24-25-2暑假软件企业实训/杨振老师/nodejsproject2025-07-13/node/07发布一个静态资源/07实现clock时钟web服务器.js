/*
把文件的实际存放路径，作为每个资源请求的url地址
在浏览器中访问如下链接：
/clock/index.html
/clock/index.css
/clock/index.js
客户端请求回来的不是具体的文件，而是文件中所存储的字符串。
要求是用fs文件把他读取出来，服务器充当的角色是字符串搬运工
 */


const http = require('http');
const fs = require('fs');
const path = require('path');

const server = http.createServer((req, res) => {
    const url = req.url;
    console.log('请求URL:', url);

    // 修正路径：从当前js文件所在目录出发，找到clock目录
    let filePath = path.join(__dirname, 'clock', url);

    // 处理直接访问/的情况，默认返回index.html
    if (url === '/') {
        filePath = path.join(__dirname, 'clock', 'index.html');
    }

    // 设置Content-Type
    let contentType = 'text/html; charset=utf-8';
    if (url.endsWith('.css')) {
        contentType = 'text/css';
    } else if (url.endsWith('.js')) {
        contentType = 'text/javascript';
    }

    fs.readFile(filePath, 'utf8', (err, data) => {
        if (err) {
            console.error('文件读取错误:', err);
            if (err.code === 'ENOENT') {
                res.writeHead(404, { 'Content-Type': 'text/html; charset=utf-8' });
                return res.end('404 文件未找到');
            }
            res.writeHead(500);
            return res.end('服务器错误');
        }

        res.writeHead(200, { 'Content-Type': contentType });
        res.end(data);
    });
});

server.listen(3000, () => {
    console.log('服务器运行在 http://localhost:3000');
    console.log('可以访问以下地址:');
    console.log('http://localhost:3000/index.html');
    console.log('http://localhost:3000/index.css');
    console.log('http://localhost:3000/index.js');
});