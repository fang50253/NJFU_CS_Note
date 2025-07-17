const express = require('express');
const app = express();
const imageRouter = require('./router/ImageRouter.js');
const cors = require('cors');

// 中间件配置（必须）
app.use(cors());
app.use(express.json({ limit: '10mb' }));  // 增加限制以适应大图
app.use(express.urlencoded({ extended: true, limit: '10mb' }));

// 路由处理
app.post("/checkImg", async (req, res) => {
    try {
        console.log('收到请求，数据长度:', req.body.img1?.length || 0);

        if (!req.body.img1) {
            return res.status(400).json({ error: "缺少图片参数 img1" });
        }

        const result = await imageRouter.main(req.body.img1);
        res.json(result);
    } catch (error) {
        console.error('服务器错误:', error);
        res.status(500).json({
            error: "内部服务器错误",
            detail: error.message,
            stack: process.env.NODE_ENV === 'development' ? error.stack : undefined
        });
    }
});

app.listen(3000, () => {
    console.log('服务已启动: http://127.0.0.1:3000');
});