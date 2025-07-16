//导入express模块
const express = require('express');
//创建app
const app = express();

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
//启动服务
app.listen(3000, () => {
    console.log('express server running at http://127.0.0.1:3000');
})