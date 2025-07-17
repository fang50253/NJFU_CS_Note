const axios = require('axios');
const AK = "9vFjFim6v5W3JjrMIvy92Urn";
const SK = "Dlju31njw9uxgorSM2YbnmoAyt6utAOx";

async function main(file) {
    // 参数验证
    if (!file || typeof file !== 'string') {
        throw new Error("无效的图片数据: 必须是base64字符串");
    }

    // 清理base64数据
    const pureBase64 = file.startsWith('data:') ? file.split(',')[1] : file;
    if (!pureBase64.match(/^[A-Za-z0-9+/]+={0,2}$/)) {
        throw new Error("无效的base64格式");
    }

    try {
        // 获取access_token
        const access_token = await getAccessToken();
        console.log('获取access_token成功');

        // 调用百度API
        const response = await axios({
            method: 'POST',
            url: `https://aip.baidubce.com/rest/2.0/image-classify/v2/advanced_general?access_token=${access_token}`,
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded',
                'Accept': 'application/json'
            },
            data: `image=${encodeURIComponent(pureBase64)}&baike_num=1`,
            timeout: 10000  // 10秒超时
        });

        // 验证响应
        if (!response.data || response.data.error_code) {
            throw new Error(response.data?.error_msg || '无效的API响应');
        }

        return response.data.result || [];
    } catch (error) {
        console.error('百度API错误:', error.response?.data || error.message);
        throw new Error(`图像识别失败: ${error.message}`);
    }
}

async function getAccessToken() {
    const url = `https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=${AK}&client_secret=${SK}`;

    const response = await axios.get(url, { timeout: 5000 });
    if (!response.data.access_token) {
        throw new Error('获取access_token失败');
    }
    return response.data.access_token;
}

module.exports = { main };