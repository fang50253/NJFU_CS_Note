//导入express模块
const express = require('express');
//创建app
const app = express();

const cors = require('cors');
app.use(cors());
//创建路由处理函数
app.use(express.urlencoded({ extended: false }))

app.get('/add',(req,res)=>{
    //返回学生信息接口
    res.send({
        status:200,
        message:"添加成功",
        data:[
            {
                name:"张三",
                sex:"男"
            },
        ]
    })
})

app.post('/get',(req,res)=>{
    const {name,sex}=req.body;
    res.send({
        status:200,
        message:"post方式获取学生信息成功",
        data:[
            {
                name:name,
                sex:sex
            },
        ]
    })
})
//启动服务
app.listen(3000, () => {
    console.log('express server running at http://127.0.0.1:3000');
})