const axios = require('axios');
const fs = require('fs');
const AK = "9vFjFim6v5W3JjrMIvy92Urn"
const SK = "Dlju31njw9uxgorSM2YbnmoAyt6utAOx"

async function main(file) {
    try {
        const access_token = await getAccessToken();
        console.log('Access Token:', access_token); // 调试日志

        // 确保 file 是纯 base64（移除 data:image/... 前缀）
        const pureBase64 = file.split(',')[1] || file;

        var options = {
            'method': 'POST',
            'url': `https://aip.baidubce.com/rest/2.0/image-classify/v2/advanced_general?access_token=${access_token}`,
            'headers': {
                'Content-Type': 'application/x-www-form-urlencoded',
                'Accept': 'application/json'
            },
            data: `image=${encodeURIComponent(pureBase64)}&baike_num=1`
        };

        const response = await axios(options);
        console.log('Full API response:', response.data); // 打印完整响应

        if (!response.data.result) {
            throw new Error('API returned unexpected structure: ' + JSON.stringify(response.data));
        }

        return response.data.result;
    } catch (error) {
        console.error('Error in image recognition:', error.response?.data || error.message);
        throw error; // 重新抛出错误以便上层捕获
    }
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
function getFileContentAsBase64(filePath){
    return new Promise((resolve, reject) => {
        fs.readFile(filePath, { encoding: 'base64' }, function (err, data) {
            if (err) {
                reject(err)
            } else {
                resolve(data)
            }
        })
    })
}
//main("/Users/fang50253/Desktop/IMG_2703.jpeg").then(res=>console.log(res));
//共享main方法
module.exports={
     main
}