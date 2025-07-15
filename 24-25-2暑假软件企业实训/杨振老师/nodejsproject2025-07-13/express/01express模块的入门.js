//导入express模块
const express = require('express');
//创建app
const app = express();

//创建路由处理函数
app.get('/', (req, res) => {
    res.send('hello world');
})

app.get("/add",(req,res)=>{
    //获取上传参数
    const {name,age}=req.query;
    res.send(`<h1>${name}---${age}</h1>`)
})

app.post("/update",(req,res)=>{
    res.send('post---update----');
});

app.delete("/update",(req,res)=>{
    res.send('delete---update----');
})

app.put("/update",(req,res)=>{
    res.send('put---update----');
})
//启动服务
app.listen(3000, () => {
    console.log('express server running at http://127.0.0.1:3000');
})