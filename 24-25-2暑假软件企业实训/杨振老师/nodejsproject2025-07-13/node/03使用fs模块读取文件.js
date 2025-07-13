//1.导入fs模块
var fs = require('fs');

//2.读取a.txt文件的文件内容
var data = fs.readFileSync('a.txt','utf8');
{
    console.log(data);
}