const express = require('express');
const https = require('https');
const cors = require('cors');
const app = express();


const AK = "eXUrfuVavHAEKw9XG1Bs0t5V"
const SK = "ddmGFHQAFAc8Cn0QSF6yxlbGrVJGL7fI"

app.use(express.json({ limit: '50mb' }));
app.use(express.urlencoded({ limit: '50mb', extended: true }));
app.use(cors());
// 获取Access Token（与翻译接口共用）
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

// 人脸对比接口
app.post('/face/match', async (req, res) => {
    console.log('收到人脸对比请求:', req.body);

    try {
        const { images } = req.body;

        // 参数验证
        if (!images || !Array.isArray(images) || images.length !== 2) {
            return res.status(400).json({
                error: '需要提供两张图片进行对比',
                error_code: 'INVALID_IMAGE_COUNT'
            });
        }

        // 验证每张图片的参数
        for (const [index, image] of images.entries()) {
            if (!image.image || !image.image_type) {
                return res.status(400).json({
                    error: `第${index + 1}张图片缺少必要参数`,
                    error_code: 'MISSING_IMAGE_PARAM'
                });
            }

            // 可选参数默认值
            image.face_type = image.face_type || 'LIVE';
            image.quality_control = image.quality_control || 'NONE';
            image.liveness_control = image.liveness_control || 'NONE';
        }

        const token = await getAccessToken();
        const postData = JSON.stringify(images);

        console.log('发送给百度人脸API的数据:', postData);

        const options = {
            hostname: 'aip.baidubce.com',
            path: `/rest/2.0/face/v3/match?access_token=${token}`,
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Content-Length': Buffer.byteLength(postData)
            }
        };

        const apiReq = https.request(options, (apiRes) => {
            let data = '';
            apiRes.on('data', (chunk) => data += chunk);
            apiRes.on('end', () => {
                console.log('百度人脸API响应:', data);
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
                error: '请求人脸对比服务失败',
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

app.listen(3000, () => console.log('Server running on http://localhost:3000'));
