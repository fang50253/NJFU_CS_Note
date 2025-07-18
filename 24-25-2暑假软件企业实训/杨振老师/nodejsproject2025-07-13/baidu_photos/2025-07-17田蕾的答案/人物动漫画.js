const express = require('express');
const https = require('https');
const cors = require('cors');
const app = express();

const AK = "l5IxI1pcLyWReecETxdtBeZf"; //
const SK = "I7RtbvC8m9fmOs9X2NNSPvmGeNQPSrdA";

app.use(express.json({ limit: '50mb' }));
app.use(express.urlencoded({ limit: '50mb', extended: true }));
app.use(cors());

// 获取Access Token
function getAccessToken() {
    return new Promise((resolve, reject) => {
        const options = {
            hostname: 'aip.baidubce.com',
            path: `/oauth/2.0/token?grant_type=client_credentials&client_id=${AK}&client_secret=${SK}`,
            method: 'POST'
        };

        const req = https.request(options, (res) => {
            let data = '';
            res.on('data', (chunk) => data += chunk);
            res.on('end', () => {
                try {
                    const result = JSON.parse(data);
                    resolve(result.access_token);
                } catch (e) {
                    reject(e);
                }
            });
        });

        req.on('error', (e) => reject(e));
        req.end();
    });
}

// 人物动漫化接口
app.post('/image/anime', async (req, res) => {
    console.log('收到动漫化请求');

    try {
        const { image, type = 'anime', mask_id = '1' } = req.body;

        // 参数验证
        if (!image || !image.image) {
            return res.status(400).json({
                error: '需要提供图片数据',
                error_code: 'MISSING_IMAGE_PARAM'
            });
        }

        const token = await getAccessToken();
        const postData = `type=${type}&mask_id=${mask_id}&image=${encodeURIComponent(image.image)}`;

        const options = {
            hostname: 'aip.baidubce.com',
            path: `/rest/2.0/image-process/v1/selfie_anime?access_token=${token}`,
            method: 'POST',
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded',
                'Content-Length': Buffer.byteLength(postData)
            }
        };

        const apiReq = https.request(options, (apiRes) => {
            let data = '';
            apiRes.on('data', (chunk) => data += chunk);
            apiRes.on('end', () => {
                console.log('百度动漫化API响应:', data);
                try {
                    const result = JSON.parse(data);
                    if (result.error_code) {
                        res.status(400).json(result);
                    } else {
                        res.json(result);
                    }
                } catch (e) {
                    res.status(500).json({
                        error: '解析响应失败',
                        details: e.message
                    });
                }
            });
        });

        apiReq.on('error', (e) => {
            res.status(500).json({
                error: '请求动漫化服务失败',
                details: e.message
            });
        });

        apiReq.write(postData);
        apiReq.end();

    } catch (error) {
        res.status(500).json({
            error: '服务器内部错误',
            message: error.message,
            stack: process.env.NODE_ENV === 'development' ? error.stack : undefined
        });
    }
});

app.listen(3002, () => console.log('动漫化服务运行在 http://localhost:3002'));