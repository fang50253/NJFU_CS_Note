const express = require('express');
const https = require('https');
const cors = require('cors');
const app = express();

const AK = "0hZgDUFLmWE9ZvqZpEWHACgU";
const SK = "Dj9HJ1cYhaczps58v6fCUb477wsZvMe4";

app.use(express.json());
app.use(cors());

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

app.post('/translate', async (req, res) => {
    console.log('收到请求:', req.body); // 调试日志

    try {
        const { text, from = 'auto', to = 'zh' } = req.body;

        // 参数验证
        if (!text || typeof text !== 'string') {
            return res.status(400).json({
                error: '缺少翻译文本',
                error_code: 'MISSING_TEXT'
            });
        }

        if (!['zh', 'en', 'jp', 'kor'].includes(to)) { // 添加所有支持的语言
            return res.status(400).json({
                error: '不支持的目标语言',
                error_code: 'INVALID_TARGET_LANG'
            });
        }

        const token = await getAccessToken();
        const postData = JSON.stringify({
            q: text, // 确保使用百度API要求的参数名"q"
            from: from === 'auto' ? 'auto' : from, // 自动检测源语言
            to: to
        });

        console.log('发送给百度API的数据:', postData); // 调试

        const options = {
            hostname: 'aip.baidubce.com',
            path: `/rpc/2.0/mt/texttrans/v1?access_token=${token}`,
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
                console.log('百度API响应:', data); // 调试
                try {
                    const result = JSON.parse(data);
                    if (result.error_code) {
                        res.status(400).json(result); // 传递百度API的错误
                    } else {
                        res.json(result);
                    }
                } catch (e) {
                    res.status(500).json({ error: '解析响应失败' });
                }
            });
        });

        apiReq.on('error', (e) => {
            res.status(500).json({ error: '请求翻译服务失败' });
        });

        apiReq.write(postData);
        apiReq.end();

    } catch (error) {
        res.status(500).json({ error: '服务器内部错误' });
    }
});

app.listen(3000, () => console.log('Server running on http://localhost:3000'));