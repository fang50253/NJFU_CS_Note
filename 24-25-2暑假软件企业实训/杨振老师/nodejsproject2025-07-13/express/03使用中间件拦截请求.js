//导入express模块
const express = require('express');
//创建app
const app = express();
//创建一个中间件
function mw(req,res,next){
    console.log('中间件执行了');
    next();
}
//加载中间件
app.use(mw);
//创建路由处理函数
app.get('/add',(req,res)=>{
    res.send('hello express')
})
//启动服务
app.listen(3000, () => {
    console.log('express server running at http://127.0.0.1:3000/add');
})