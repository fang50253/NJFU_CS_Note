//导入express
const express = require('express');
//创建应用对象
const app = express();
//导入图像识别模块
const imageRouter=require('./router/ImageRouter.js')
//导入cors
const cors=require('cors');
app.use(cors());
// 需要添加 express.json() 中间件来解析 JSON 请求体
app.use(express.json());

app.post("/checkImg",(req,res)=>{
    let file=req.query.img1;
    imageRouter.main(file).then(result=>{
        res.send(result);
    })
})

//启动服务
app.listen(3000, () => {
    console.log('http://127.0.0.1:3000');
})