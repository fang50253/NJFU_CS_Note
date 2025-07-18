//海螺key：eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJHcm91cE5hbWUiOiLmlrnms73lrociLCJVc2VyTmFtZSI6IuaWueazveWuhyIsIkFjY291bnQiOiIiLCJTdWJqZWN0SUQiOiIxOTQ1NDg3NzAwMzU4MzM3MTYxIiwiUGhvbmUiOiIxODg5NjY5ODU2NiIsIkdyb3VwSUQiOiIxOTQ1NDg3NzAwMzQ5OTQ4NTUzIiwiUGFnZU5hbWUiOiIiLCJNYWlsIjoiIiwiQ3JlYXRlVGltZSI6IjIwMjUtMDctMTggMDk6MjA6MDMiLCJUb2tlblR5cGUiOjEsImlzcyI6Im1pbmltYXgifQ.MkqWYi3p68gm9IxoX0QbXtgWcAXUR7ulpp4qD98Iv7ejoHktQOe-0250Divnj__2DZdI2HUrZBxASjo6eqU6iEdaU44t5IW3_qdPzGzrrSfQr-Tu1YBPc6rqF3PVAGvPC6sC5ZEHmIuHHTl7j8yod0cJYR1pxGNYtXBgtwsf-yA8uYipCFlGqSC6R27JoLqiHwa-p6eYlxD7htsOXNkff27Yp5nTT0U6OnlSP-05UqziwxU4DiVUboC2WkcoYe_kPTaXKYbwhm-zoc_UgPDvMUTlYVnchFpP0UH-a6NNCHvG7CSvfkpuOSpJ9eygOhufZ_9dwBLg4tsumBBIMB58Qg

const express = require('express');
const cors = require('cors');
const axios = require('axios');
const bodyParser = require('body-parser');
//黑白图片上色https://console.bce.baidu.com/ai-engine/imageprocess/overview/index
const app = express();
app.use(cors());
app.use(bodyParser.json({ limit: '10mb' }));

const group_id = "1945487700349948553";
const api_key = "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJHcm91cE5hbWUiOiLmlrnms73lrociLCJVc2VyTmFtZSI6IuaWueazveWuhyIsIkFjY291bnQiOiIiLCJTdWJqZWN0SUQiOiIxOTQ1NDg3NzAwMzU4MzM3MTYxIiwiUGhvbmUiOiIxODg5NjY5ODU2NiIsIkdyb3VwSUQiOiIxOTQ1NDg3NzAwMzQ5OTQ4NTUzIiwiUGFnZU5hbWUiOiIiLCJNYWlsIjoiIiwiQ3JlYXRlVGltZSI6IjIwMjUtMDctMTggMDk6MjA6MDMiLCJUb2tlblR5cGUiOjEsImlzcyI6Im1pbmltYXgifQ.MkqWYi3p68gm9IxoX0QbXtgWcAXUR7ulpp4qD98Iv7ejoHktQOe-0250Divnj__2DZdI2HUrZBxASjo6eqU6iEdaU44t5IW3_qdPzGzrrSfQr-Tu1YBPc6rqF3PVAGvPC6sC5ZEHmIuHHTl7j8yod0cJYR1pxGNYtXBgtwsf-yA8uYipCFlGqSC6R27JoLqiHwa-p6eYlxD7htsOXNkff27Yp5nTT0U6OnlSP-05UqziwxU4DiVUboC2WkcoYe_kPTaXKYbwhm-zoc_UgPDvMUTlYVnchFpP0UH-a6NNCHvG7CSvfkpuOSpJ9eygOhufZ_9dwBLg4tsumBBIMB58Qg";

app.post('/ask', async (req, res) => {
    const userInput = req.body.prompt;
    if (!userInput) return res.status(400).send('缺少 prompt');

    const requestBody = {
        model: "minimax-text-01",
        messages: [
            { role: "system", content: "你是一个中文助手。" },
            { role: "user", content: userInput }
        ],
        stream: false,
        max_tokens: 256,
        temperature: 0.1,
        top_p: 0.95
    };
    try {
        const response = await axios.post(
            `https://api.minimax.chat/v1/text/chatcompletion_v2?GroupId=${group_id}`,
            requestBody,
            {
                headers: {
                    "Content-Type": "application/json",
                    "Authorization": `Bearer ${api_key}`
                }
            }
        );
        const aiText = response.data.choices?.[0]?.message?.content || 'AI 无回复';
        res.send(aiText);
    } catch (err) {
        console.error('MiniMax 错误:', err.response?.data || err.message);
        res.status(500).send('AI 请求失败');
    }
});

app.listen(3000, '127.0.0.1', () => {
    console.log('服务器运行于 http://127.0.0.1:3000');
});