import java.util.*; // 导入 Java 实用工具包

/**
 * Question3Pro 类：用于统计输入字符串中每个单词的出现次数。
 */
class Question3Pro {
    public static void main(String[] args) {
        // 创建一个 HashMap，用于存储单词及其对应的出现次数
        Map<String, Integer> cnt = new HashMap<>();

        // 创建 Scanner 对象，用于从控制台读取输入
        Scanner scanner = new Scanner(System.in);

        // 提示用户输入一行文本
        System.out.println("请输入一段文本：");

        // 读取用户输入的整行字符串
        String str = scanner.nextLine();

        /**
         * 使用正则表达式 "[\\W]" 对输入字符串进行分割：
         * - \\W 表示非单词字符（即非字母、数字或下划线），如空格、标点符号等
         * - 分割后的结果存储在字符串数组 words 中
         */
        String words[] = str.split("[\\W]");

        // 遍历分割后的每个单词
        for (String x : words) {
            // 如果单词为空字符串，则跳过
            if (x.isEmpty()) continue;

            // 判断 HashMap 中是否已包含该单词
            if (cnt.containsKey(x)) {
                // 如果包含，更新该单词的计数值（加 1）
                cnt.put(x, cnt.get(x) + 1);
            } else {
                // 如果不包含，将该单词加入 HashMap，初始计数值为 1
                cnt.put(x, 1);
            }
        }

        // 打印 HashMap 中存储的单词及其出现次数
        System.out.println("单词统计结果：" + cnt);

        // 关闭 Scanner 对象，防止资源泄漏
        scanner.close();
    }
}