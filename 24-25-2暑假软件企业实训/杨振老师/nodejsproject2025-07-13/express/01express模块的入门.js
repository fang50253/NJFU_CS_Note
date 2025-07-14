//导入express模块
const express = require('express');
//创建app
const app = express();

//创建路由处理函数
app.get('/', (req, res) => {
    res.send('hello world');
})

//启动服务
app.listen(3000, () => {
    console.log('express server running at http://127.0.0.1:3000');
})