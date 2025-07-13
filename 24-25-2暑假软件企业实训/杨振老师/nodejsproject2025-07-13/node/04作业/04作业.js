const fs = require('fs');

// 1. 读取 成绩.txt
fs.readFile('成绩.txt', 'utf8', (err, data) => {
  if (err) {
    console.error('读取文件失败:', err);
    return;
  }

  // 2. 处理数据：按空格拆分，再按 "=" 拆分，并格式化为 "名字：分数" 的形式
  const formattedData = data
    .split(' ') // 拆分成 ["小红=99", "小白=100", ...]
    .map(item => {
      const [name, score] = item.split('='); // 拆分成 ["小红", "99"] 等
      return `${name}：${score}`; // 格式化为 "小红：99"
    })
    .join('\n'); // 用换行符拼接

  // 3. 写入到 成绩.ok 文件
  fs.writeFile('成绩.ok', formattedData, 'utf8', (err) => {
    if (err) {
      console.error('写入文件失败:', err);
      return;
    }
    console.log('成功写入到 成绩.ok 文件！');
  });
});