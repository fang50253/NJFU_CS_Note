const express = require('express');
const path = require('path');
const app = express();

// 方法1：使用 __dirname (推荐)
app.use("/init",express.static(path.join(__dirname, 'clock')));

app.use("/clock",express.static("../node/2025-07-14检查的作业/11apiserver.html"));
// 方法2：使用 process.cwd() (如果 clock 目录在工作目录下)
// app.use(express.static(path.join(process.cwd(), 'clock')));

app.listen(3000, () => {
    console.log('Server running at http://localhost:3000');
    console.log('__dirname:', __dirname);
    console.log('process.cwd():', process.cwd());
});