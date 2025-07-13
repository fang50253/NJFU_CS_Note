//1.导入fs模块
const fs = require('fs');

//2.把“我爱学习”写入到a.txx文件中
fs.writeFile('a.txt', '我爱学习', function (err) {
    if (err) throw err;
    console.log('写入成功');
})