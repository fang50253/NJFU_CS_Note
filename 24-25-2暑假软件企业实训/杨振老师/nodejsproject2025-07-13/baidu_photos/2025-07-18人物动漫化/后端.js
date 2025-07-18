const express = require('express');
const https = require('https');
const cors = require('cors');
const app = express();
//黑白图片上色后端：https://console.bce.baidu.com/ai-engine/imageprocess/overview/index
app.use(cors());


const AK = "1KYdvQsyWfK48mAMl3OeH9oq"
const SK = "IIBfWkKDVHcsA1YnA2arXWcfh5xG00Ap"

async function main(file) {
    var options = {
        'method': 'POST',
        'url': 'https://aip.baidubce.com/rest/2.0/image-process/v1/colourize?access_token=' + await getAccessToken(),
        'headers': {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Accept': 'application/json'
        },
        data: {
            "image":file
        }
    };

    axios(options)
        .then(response => {
            console.log(response.data);
        })
        .catch(error => {
            throw new Error(error);
        })
    return new Promise((resolve, reject) => {
        axios(options)
            .then(res => {
                resolve(res.data.image)
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

app.post('/upload', async function (req, res) {
    res.send(await main(req[0]));
})

app.listen(3000, function () {
    console.log('http://127.0.0.1:3000/');
})