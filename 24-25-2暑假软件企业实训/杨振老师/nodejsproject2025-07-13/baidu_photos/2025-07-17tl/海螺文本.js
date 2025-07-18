const express = require('express');
const https = require('https');
const cors = require('cors');
const app = express();

// Configuration - replace these with your actual API credentials
const GROUP_ID = "1945487700349948258";
const API_KEY = "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJHcm91cE5hbWUiOiLnlLDolb4iLCJVc2VyTmFtZSI6IueUsOiVviIsIkFjY291bnQiOiIiLCJTdWJqZWN0SUQiOiIxOTQ1NDg3NzAwMzU4MzM2ODY2IiwiUGhvbmUiOiIxOTM5Mzg5ODU5MiIsIkdyb3VwSUQiOiIxOTQ1NDg3NzAwMzQ5OTQ4MjU4IiwiUGFnZU5hbWUiOiIiLCJNYWlsIjoiIiwiQ3JlYXRlVGltZSI6IjIwMjUtMDctMTcgMTU6Mzg6MjQiLCJUb2tlblR5cGUiOjEsImlzcyI6Im1pbmltYXgifQ.EctTEbWWCQghiE-hTSZkuRc4ppNTMR0r9-hB82_b_h9gFRyH6yNaqpM3hdnGHhxSjPuHlxBFW7JKBF47I9BchIS_nK8FYlBkhLJuI21IOBPA7Bo0v7RBOBQWfMoXNrQN2mZ_noORxYcON49_aLWQ6uJzdXu3DJVRkMsqusswtVFekncrzsqbDzcfw0eZ6pTv7vJhGtlpP4yavGOwTBH2wZzOqyVOg4mVsUbUpHcfk5hgfpQqvkUeynmwAp97DkCdV7TwMqbHaaJhcM7QrbXFAhEynUVpiuK1U_eIPDZbScjs6fShb_g_13Hy_QSnU49bIfw0AbAt8Fr6zkyMeSJwOw";

app.use(express.json({ limit: '50mb' }));
app.use(express.urlencoded({ limit: '50mb', extended: true }));
app.use(cors());

// Text analysis/conversation endpoint
app.post('/text/analyze', async (req, res) => {
    console.log('收到文本分析请求:', req.body);

    try {
        const { message, history = [] } = req.body;

        // Parameter validation
        if (!message) {
            return res.status(400).json({
                error: '需要提供消息内容',
                error_code: 'MISSING_MESSAGE'
            });
        }

        // Prepare the request body for MiniMax API
        const requestBody = {
            "model": "minimax-text-01",
            "messages": [
                {
                    "content": "你是一个智能AI助手，能够帮助用户分析文本并提供有见地的回答。",
                    "role": "system",
                    "name": "AI Assistant"
                },
                ...history,
                {
                    "content": message,
                    "role": "user",
                    "name": "User"
                }
            ],
            "stream": false,
            "max_tokens": 512,
            "temperature": 0.7,
            "top_p": 0.95
        };

        const options = {
            hostname: 'api.minimax.chat',
            path: `/v1/text/chatcompletion_v2?GroupId=${GROUP_ID}`,
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': `Bearer ${API_KEY}`,
                'Content-Length': Buffer.byteLength(JSON.stringify(requestBody))
            }
        };

        const apiReq = https.request(options, (apiRes) => {
            let data = '';
            apiRes.on('data', (chunk) => data += chunk);
            apiRes.on('end', () => {
                console.log('MiniMax API响应:', data);
                try {
                    const result = JSON.parse(data);
                    if (result.base_resp?.status_code !== 0) {
                        res.status(400).json({
                            error: 'API请求失败',
                            details: result.base_resp?.status_msg || '未知错误'
                        });
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
                error: '请求文本分析服务失败',
                details: e.message
            });
        });

        apiReq.write(JSON.stringify(requestBody));
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