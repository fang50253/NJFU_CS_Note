const axios = require('axios');
const AK = "jZrSTU****zuNziF"
const SK = "9quy0T****CJpEBk"

async function main(file) {
    var options = {
        'method': 'POST',
        'url': 'https://aip.baidubce.com/rest/2.0/image-classify/v2/advanced_general?access_token=' + await getAccessToken(),
        'headers': {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Accept': 'application/json'
        },
        // image 可以通过 getFileContentAsBase64("C:\fakepath\微信图片_20250717090148.jpg") 方法获取,
        data: {
            'image': getFileContentAsBase64(file),
            'baike_num': 1
        }
    };
//删除这段代码
    //axios(options)
    // .then(response => {
    //   console.log(response.data);
    //})
    //.catch(error => {
    //  throw new Error(error);
    //})
//}
    return new Promise((resolve, reject) => {
        axios(options)
            .then(res => {
                resolve(res.data.result[0])
            })
            .catch(error => {
                reject(error)
            })
    })
}
/**
 * 使用 AK，SK 生成鉴权签名（Access Token）
 * @return string 鉴权签名信息（Access Token）
 */
function getAccessToken() {

    let options = {
        'method': 'POST',
        'url': 'https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=' + AK + '&client_secret=' + SK,
    }
    return new Promise((resolve, reject) => {
        axios(options)
            .then(res => {
                resolve(res.data.access_token)
            })
            .catch(error => {
                reject(error)
            })
    })
}

/**
 * 获取文件base64编码
 * @param string  path 文件路径
 * @return string base64编码信息，不带文件头
 */
function getFileContentAsBase64(path) {
    const fs = require('fs');
    try {
        return fs.readFileSync(path, { encoding: 'base64' });
    } catch (err) {
        throw new Error(err);
    }
}
main("C:\\fakepath\\ttlqx.jpg").then( res=>{
    console.log(res)
})