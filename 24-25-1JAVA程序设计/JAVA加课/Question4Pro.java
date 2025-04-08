/**
 * Question4Pro 类：计算每天切割某物体长度的操作所需的天数，直到长度小于指定值。
 */
public class Question4Pro {

    /**
     * cut 方法：模拟每天减少物体长度的过程，计算操作天数。
     * 
     * @return 需要的天数。
     */
    public static int cut() {
        // 初始化操作天数为 0
        int d = 0;

        // 初始长度设置为 150000
        for (double l = 150000;; l = l - l / 5, d++) {
            // 打印当前长度，便于调试和查看过程
            System.out.println("当前长度 l: " + l);

            /**
             * 判断条件：
             * - 如果当前长度在 [0, 1.25) 区间内，则结束循环。
             * - l >= 0 是为了确保长度非负。
             * - l < 1.25 是最终的停止条件。
             */
            if (l >= 0 && l < 1.25) {
                break;
            }
        }

        // 返回总共需要的天数
        return d;
    }

    /**
     * 主方法：程序的入口，调用 cut 方法并输出结果。
     */
    public static void main(String[] args) {
        // 打印计算所需的总天数
        System.out.println("所需天数: " + cut());
    }
}