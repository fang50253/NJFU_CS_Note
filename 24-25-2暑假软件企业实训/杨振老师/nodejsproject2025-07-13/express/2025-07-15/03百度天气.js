const express = require('express');
const https = require('https'); // 使用 Node.js 内置 https 模块
const app = express();
const port = 3000;

// 百度地图AK - 建议通过环境变量配置
const BAIDU_MAP_AK = process.env.BAIDU_MAP_AK || '这里加上你的ak';

// 获取玄武区天气的路由
app.get('/weather/xuanwu', (req, res) => {
    // 1. 直接使用行政区划代码获取天气
    const options = {
        hostname: 'api.map.baidu.com',
        path: `/weather/v1/?district_id=320102&data_type=all&ak=${BAIDU_MAP_AK}`,
        method: 'GET'
    };

    const request = https.request(options, (apiRes) => {
        let data = '';

        apiRes.on('data', (chunk) => {
            data += chunk;
        });

        apiRes.on('end', () => {
            try {
                const weatherData = JSON.parse(data);

                // 2. 检查返回数据是否有效
                if (!weatherData || !weatherData.result) {
                    throw new Error('无效的天气数据');
                }

                // 3. 提取并返回简洁的天气信息
                const currentWeather = weatherData.result.now;
                const responseData = {
                    district: '玄武区',
                    weather: currentWeather.text,
                    temperature: currentWeather.temp + '℃',
                    wind: `${currentWeather.wind_dir} ${currentWeather.wind_class}级`,
                    updateTime: new Date(weatherData.result.forecasts[0].update_time).toLocaleString()
                };

                res.json(responseData);
            } catch (error) {
                console.error('解析天气数据失败:', error.message);
                res.status(500).json({
                    error: '解析天气信息失败',
                    detail: error.message
                });
            }
        });
    });

    request.on('error', (error) => {
        console.error('请求天气API失败:', error.message);
        res.status(500).json({
            error: '请求天气API失败',
            detail: error.message
        });
    });

    request.end();
});

app.listen(port, () => {
    console.log(`天气服务已启动: http://localhost:${port}/weather/xuanwu`);
});