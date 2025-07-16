//导入express模块
const express = require('express');
//创建app
const app = express();

app.use(express.urlencoded({ extended: false }));

//创建路由处理函数
app.post('/add',(req,res)=>{
    const {name,sex}=req.body;
    res.send(`<h1>${name}----${sex}</h1>`);
})
//启动服务
app.get("/getStudent",(req,res)=>{
    res.send({
        status:200,
        data:{
            name:"张三",
            sex:"男"
        }
    });
})
app.listen(3000, () => {
    console.log('express server running at http://127.0.0.1:3000');
})