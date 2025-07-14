console.log("-----我的自定义模块-----")

let name="jack"
let sex="男"
let age=18

function study(){
    console.log("我爱学习")
}

//共享name和study
module.exports={
    name,
    age,
    sex,
    study
}