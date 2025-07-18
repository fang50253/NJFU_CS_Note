const express = require('express');
const cors = require('cors');
const axios = require('axios');

const app = express();
app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

const API_KEY = "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJHcm91cE5hbWUiOiLmlrnms73lrociLCJVc2VyTmFtZSI6IuaWueazveWuhyIsIkFjY291bnQiOiIiLCJTdWJqZWN0SUQiOiIxOTQ1NDg3NzAwMzU4MzM3MTYxIiwiUGhvbmUiOiIxODg5NjY5ODU2NiIsIkdyb3VwSUQiOiIxOTQ1NDg3NzAwMzQ5OTQ4NTUzIiwiUGFnZU5hbWUiOiIiLCJNYWlsIjoiIiwiQ3JlYXRlVGltZSI6IjIwMjUtMDctMTggMDk6MjA6MDMiLCJUb2tlblR5cGUiOjEsImlzcyI6Im1pbmltYXgifQ.MkqWYi3p68gm9IxoX0QbXtgWcAXUR7ulpp4qD98Iv7ejoHktQOe-0250Divnj__2DZdI2HUrZBxASjo6eqU6iEdaU44t5IW3_qdPzGzrrSfQr-Tu1YBPc6rqF3PVAGvPC6sC5ZEHmIuHHTl7j8yod0cJYR1pxGNYtXBgtwsf-yA8uYipCFlGqSC6R27JoLqiHwa-p6eYlxD7htsOXNkff27Yp5nTT0U6OnlSP-05UqziwxU4DiVUboC2WkcoYe_kPTaXKYbwhm-zoc_UgPDvMUTlYVnchFpP0UH-a6NNCHvG7CSvfkpuOSpJ9eygOhufZ_9dwBLg4tsumBBIMB58Qg";; // 替换为你自己的
const group_id = "1945487700349948553";
const BASE_URL = 'https://api.minimaxi.com/v1';


app.post('/generate', async (req, res) => {
    const prompt = req.body.prompt;
    try {
        const response = await axios.post(`${BASE_URL}/video_generation`, {
            model: "MiniMax-Hailuo-02",
            prompt: prompt,
            duration: 6,
            resolution: "1080P"
        }, {
            headers: {
                Authorization: `Bearer ${API_KEY}`,
                'Content-Type': 'application/json'
            }
        });
        res.json({ task_id: response.data.task_id });
    } catch (err) {
        console.error('生成任务失败：', err.response?.data || err.message);
        res.status(500).json({ error: '任务提交失败' });
    }
});

app.get('/status', async (req, res) => {
    const task_id = req.query.task_id;
    try {
        const response = await axios.get(`${BASE_URL}/query/video_generation?task_id=${task_id}`, {
            headers: {
                Authorization: `Bearer ${API_KEY}`,
                'Content-Type': 'application/json'
            }
        });

        const status = response.data.status;
        if (status === 'Success') {
            const file_id = response.data.file_id;
            const fileRes = await axios.get(`${BASE_URL}/files/retrieve?file_id=${file_id}`, {
                headers: {
                    Authorization: `Bearer ${API_KEY}`
                }
            });
            const download_url = fileRes.data.file.download_url;
            res.json({ status, download_url });
        } else {
            res.json({ status });
        }
    } catch (err) {
        console.error('查询任务失败：', err.response?.data || err.message);
        res.status(500).json({ error: '查询失败' });
    }
});

app.listen(3000, () => {
    console.log('✅ 视频生成服务运行在 http://127.0.0.1:3000');
});