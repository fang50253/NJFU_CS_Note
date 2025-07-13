const fs = require('fs');
const path = require('path');

// 1. 定义输入和输出路径
const inputHtmlPath = path.join(__dirname, 'index.html'); // 输入文件（与脚本同目录）
const outputDir = path.join(__dirname, 'clock');          // 输出目录

// 2. 检查输入文件是否存在
if (!fs.existsSync(inputHtmlPath)) {
  console.error(`错误：未找到输入文件 ${inputHtmlPath}`);
  process.exit(1);
}

// 3. 创建输出目录（如果不存在）
if (!fs.existsSync(outputDir)) {
  fs.mkdirSync(outputDir);
}

// 4. 读取原始 HTML
const htmlContent = fs.readFileSync(inputHtmlPath, 'utf8');

// 5. 提取 CSS 和 JS
const cssMatch = htmlContent.match(/<style>([\s\S]*?)<\/style>/);
const jsMatch = htmlContent.match(/<script>([\s\S]*?)<\/script>/);

const cssContent = cssMatch ? cssMatch[1].trim() : '';
const jsContent = jsMatch ? jsMatch[1].trim() : '';

// 6. 生成新的 HTML（替换为外部引用）
const newHtml = htmlContent
  .replace(/<style>[\s\S]*?<\/style>/, '<link rel="stylesheet" href="index.css">')
  .replace(/<script>[\s\S]*?<\/script>/, '<script src="index.js"></script>');

// 7. 写入输出文件
fs.writeFileSync(path.join(outputDir, 'index.html'), newHtml);
fs.writeFileSync(path.join(outputDir, 'index.css'), cssContent);
fs.writeFileSync(path.join(outputDir, 'index.js'), jsContent);

console.log(`成功！文件已保存到 ${outputDir}`);