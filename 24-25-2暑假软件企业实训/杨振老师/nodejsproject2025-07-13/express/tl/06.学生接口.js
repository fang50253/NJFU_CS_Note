//1.导入express
const express = require('express');

//2.创建app
const app = express();

//导入cors
const cors = require('cors');

//注册cors
app.use(cors());

// 允许所有来源跨域
// app.use((req, res, next) => {
//     res.header('Access-Control-Allow-Origin', '*');
//     res.header('Access-Control-Allow-Methods', 'GET,POST');
//     res.header('Access-Control-Allow-Headers', 'Content-Type');
//     next();
// });

// 解析 JSON 请求体
app.use(express.json());

// 解析 application/x-www-form-urlencoded 请求体
app.use(express.urlencoded({ extended: false }));

//获取学生信息接口
app.get('/add', (req, res) => {
    res.send({
        status: 200,
        message: '获取学生信息成功',
        data: {
            id: 1,
            name: '张三',
            age: 18,
            class: '高一(1)班'
        }
    })
});


// 新增学生信息接口
app.post('/addStu', (req, res) => {
    const { age, name } = req.body;
    res.send({
        status: 200,
        message: '新增学生信息成功',
        data: {
            age,
            name
        }
    });
});


//4.启动服务
app.listen(3009, () => {
    console.log('Server is running on http://localhost:3009');

})