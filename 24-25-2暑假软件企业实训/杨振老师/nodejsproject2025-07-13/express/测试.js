const express = require('express');
const app = express();

// 解析 application/x-www-form-urlencoded 格式的请求体
app.use(express.urlencoded({ extended: false }));  // extended: false 使用querystring库解析

app.post('/add', (req, res) => {
    const { name, sex } = req.body;
    if (!name || !sex) {
        return res.status(400).send('Name and sex are required');
    }
    res.send(`<h1>${name}----${sex}</h1>`);
});

app.listen(3000, () => {
    console.log('Server running at http://127.0.0.1:3000');
});