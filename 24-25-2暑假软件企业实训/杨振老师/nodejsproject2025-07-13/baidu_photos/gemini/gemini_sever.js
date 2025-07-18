import { GoogleGenerativeAI } from "@google/generative-ai";

// 用你的 API Key 替换下面这一行
const genAI = new GoogleGenerativeAI("YOUR_API_KEY");

async function main() {
    const model = genAI.getGenerativeModel({ model: "gemini-1.5-flash" });

    const result = await model.generateContent([
        {
            role: "user",
            parts: [{ text: "Explain how AI works in a few words" }],
        },
    ]);

    const response = await result.response;
    const text = await response.text();
    console.log("Gemini 输出：", text);
}

main();