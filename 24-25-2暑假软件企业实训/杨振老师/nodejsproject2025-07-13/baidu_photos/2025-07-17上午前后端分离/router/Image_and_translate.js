const express = require('express');
const https = require('https');
const axios = require('axios');
const cors = require('cors');
const app = express();

const TRANSLATE_AK = "0hZgDUFLmWE9ZvqZpEWHACgU";
const TRANSLATE_SK = "Dj9HJ1cYhaczps58v6fCUb477wsZvMe4";
const IMAGE_AK = "9vFjFim6v5W3JjrMIvy92Urn";
const IMAGE_SK = "Dlju31njw9uxgorSM2YbnmoAyt6utAOx";

app.use(cors());
app.use(express.json({ limit: '10mb' }));

async function getAccessToken(ak, sk) {
    return new Promise((resolve, reject) => {
        const options = {
            hostname: 'aip.baidubce.com',
            path: `/oauth/2.0/token?grant_type=client_credentials&client_id=${ak}&client_secret=${sk}`,
            method: 'POST'
        };

        const req = https.request(options, (res) => {
            let data = '';
            res.on('data', (chunk) => data += chunk);
            res.on('end', () => {
                const result = JSON.parse(data);
                resolve(result.access_token);
            });
        });

        req.on('error', reject);
        req.end();
    });
}

app.post('/translate', async (req, res) => {
    const { text, from = 'auto', to = 'zh' } = req.body;
    const token = await getAccessToken(TRANSLATE_AK, TRANSLATE_SK);

    // 构建符合百度翻译API要求的请求数据
    const postData = {
        q: text,
        from: from,
        to: to
    };

    // 使用axios发送请求
    try {
        const response = await axios({
            method: 'POST',
            url: `https://aip.baidubce.com/rpc/2.0/mt/texttrans/v1?access_token=${token}`,
            headers: {
                'Content-Type': 'application/json',
                'Accept': 'application/json'
            },
            data: postData
        });
        res.json(response.data);
    } catch (error) {
        res.json({ error: "翻译失败" });
    }
});

app.post('/checkImg', async (req, res) => {
    const pureBase64 = req.body.img1.split(',')[1] || req.body.img1;
    const access_token = await getAccessToken(IMAGE_AK, IMAGE_SK);
    const response = await axios({
        method: 'POST',
        url: `https://aip.baidubce.com/rest/2.0/image-classify/v2/advanced_general?access_token=${access_token}`,
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        data: `image=${encodeURIComponent(pureBase64)}`
    });
    res.json(response.data.result);
});

app.listen(3000, () => console.log('Server running on http://localhost:3000'));