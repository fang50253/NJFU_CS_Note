//加载自定义模块,一定要以./或者../开头，区分自定义模块或者第三方模块
var myModule = require('./08自定义模块.js');

console.log(myModule.name)
console.log(myModule.age)
console.log(myModule.sex)
myModule.study()