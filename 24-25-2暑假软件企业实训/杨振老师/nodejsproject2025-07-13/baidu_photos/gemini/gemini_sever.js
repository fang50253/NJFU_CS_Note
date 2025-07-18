const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const { GoogleGenerativeAI } = require('@google/generative-ai');

// 替换成你的 API Key
const genAI = new GoogleGenerativeAI("AIzaSyAJ5LDV8XkTObI8vy_xeSXd2-MfBGf50uk");

const app = express();

app.use(cors());
app.use(bodyParser.json({ limit: '10mb' }));

async function askGemini(question) {
    const model = genAI.getGenerativeModel({ model: "gemini-1.5-flash" });

    // 这里传入一个字符串，兼容你之前的调用
    const result = await model.generateContent(question);

    const response = await result.response;
    const text = await response.text();

    console.log("Gemini 输出：", text);
    return text;
}

app.post('/ask', async (req, res) => {
    try {
        const prompt = req.body.prompt; // 这里改成 prompt
        console.log("接收到的 prompt：", prompt);
        if (!prompt) {
            return res.status(400).send('缺少 prompt 参数');
        }
        const answer = await askGemini(prompt);
        // 直接返回字符串，不包对象
        res.send(answer);
    } catch (err) {
        console.error(err);
        res.status(500).send('服务器内部错误');
    }
});

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`服务已启动：http://127.0.0.1:${PORT}`);
});