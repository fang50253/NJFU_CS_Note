const express = require('express');
const cors = require('cors');
const axios = require('axios');
const bodyParser = require('body-parser');
//黑白图片上色https://console.bce.baidu.com/ai-engine/imageprocess/overview/index
const app = express();
app.use(cors());
app.use(bodyParser.json({ limit: '10mb' }));


const AK = "1KYdvQsyWfK48mAMl3OeH9oq";
const SK = "IIBfWkKDVHcsA1YnA2arXWcfh5xG00Ap";
async function getAccessToken() {
    const url = `https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=${AK}&client_secret=${SK}`;
    const res = await axios.post(url);
    return res.data.access_token;
}

async function colorizeImage(base64) {
    const access_token = await getAccessToken();
    const url = `https://aip.baidubce.com/rest/2.0/image-process/v1/colourize?access_token=${access_token}`;

    const res = await axios.post(url,
        new URLSearchParams({ image: base64 }).toString(),
        { headers: { 'Content-Type': 'application/x-www-form-urlencoded' } }
    );

    return res.data.image;
}

app.post('/black', async (req, res) => {
    try {
        const base64 = req.body.file;
        const coloredBase64 = await colorizeImage(base64);
        res.json({ image: coloredBase64 });
    } catch (err) {
        console.error(err);
        res.status(500).send("处理失败");
    }
});

async function animefy(base64) {
    const access_token = await getAccessToken();
    const url = `https://aip.baidubce.com/rest/2.0/image-process/v1/selfie_anime?access_token=${access_token}`;

    const res = await axios.post(url,
        new URLSearchParams({ image: base64 }).toString(),
        { headers: { 'Content-Type': 'application/x-www-form-urlencoded' } }
    );

    return res.data.image;
}

app.post('/anime', async (req, res) => {
    try {
        const base64 = req.body.file;
        const coloredBase64 = await animefy(base64);
        res.json({ image: coloredBase64 });
    } catch (err) {
        console.error(err);
        res.status(500).send("处理失败");
    }
});


app.listen(3000, () => {
    console.log("Server running at http://127.0.0.1:3000/");
});