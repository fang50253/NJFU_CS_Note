//导入express模块
const express = require('express');
//创建app
const app = express();

// 创建三个中间件拦截器
function interceptorA(req, res, next) {
    console.log('拦截a');
    next();
}

function interceptorB(req, res, next) {
    console.log('拦截b');
    next();
}

function interceptorC(req, res, next) {
    console.log('拦截c');
    next();
}

//创建一个中间件
function mw(req, res, next) {
    console.log('中间件执行了');
    next();
}

//加载中间件（按顺序先加载三个拦截器）
app.use(interceptorA);
app.use(interceptorB);
app.use(interceptorC);
app.use(mw);

//创建路由处理函数
app.get('/add', (req, res) => {
    res.send('hello express');
    throw new Error('服务器内部错误');
});

app.use((err, req, res, next) => {
    console.log(err.message);
    res.send('错误中间件');
});

//启动服务
app.listen(3000, () => {
    console.log('express server running at http://127.0.0.1:3000/add');
});


//注意，中间件只能出现在路由的上面，而不能在下面。
//错误中间件放在路由的下面