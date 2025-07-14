const http = require('http');
const fs = require('fs');
const path = require('path');

// 创建HTTP服务器
const server = http.createServer((req, res) => {
    // 1. 获取请求的URL路径
    const url = req.url;
    console.log(`收到请求: ${url}`);

    // 2. 设置默认响应头
    res.setHeader('Content-Type', 'text/plain; charset=utf-8');

    // 3. 处理不同URL路径
    if (url === '/') {
        return res.end('欢迎访问！请尝试访问/clock/index.html、/clock/index.css或/clock/index.js');
    }

    // 4. 处理/clock/下的资源请求
    if (url.startsWith('/clock/')) {
        // 获取请求的文件名
        const fileName = url.replace('/clock/', '');

        // 定义允许访问的文件
        const allowedFiles = ['index.html', 'index.css', 'index.js'];

        if (!allowedFiles.includes(fileName)) {
            return res.end('404 请求的文件不存在');
        }

        // 构建文件路径
        const filePath = path.join(__dirname, 'clock', fileName);

        // 5. 读取文件内容
        fs.readFile(filePath, 'utf8', (err, data) => {
            if (err) {
                console.error('读取文件出错:', err);
                return res.end('500 服务器读取文件出错');
            }

            // 6. 返回文件内容作为字符串
            console.log(`返回文件内容: ${filePath}`);
            res.end(data);
        });
    } else {
        res.end('404 页面不存在');
    }
});

// 启动服务器
server.listen(3000, () => {
    console.log('服务器已启动，访问地址: http://localhost:3000');
    console.log('可以测试以下URL:');
    console.log('http://localhost:3000/clock/index.html');
    console.log('http://localhost:3000/clock/index.css');
    console.log('http://localhost:3000/clock/index.js');
});