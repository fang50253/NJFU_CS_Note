import javax.swing.*; // 导入用于创建图形界面的 Swing 包
import java.awt.event.ActionEvent; // 导入用于处理按钮事件的类
import java.awt.event.ActionListener; // 导入事件监听器接口
import java.util.*; // 导入实用工具类
import java.awt.*; // 导入 AWT 包，用于布局管理等

/**
 * 主类，继承 JFrame，用于创建图形界面并管理生成器线程。
 */
public class Question5Pro extends JFrame {
    private JLabel digits[] = new JLabel[5]; // 用于显示随机字符的标签数组
    private Generator generators[] = new Generator[5]; // 用于生成随机字符的生成器线程数组

    /**
     * 构造方法，调用 create 方法初始化界面。
     */
    public Question5Pro() {
        super(); // 调用父类构造方法
        this.create(); // 创建和初始化界面
    }

    /**
     * 创建并初始化图形界面，包括标签、按钮和线程。
     */
    private void create() {
        this.getContentPane().setLayout(new GridLayout(1, 6)); // 设置布局为 1 行 6 列

        // 创建 5 个 JLabel 标签并添加到界面中
        for (int i = 0; i < 5; i++) {
            digits[i] = new JLabel(); // 初始化标签
            digits[i].setHorizontalAlignment(SwingConstants.CENTER); // 设置文本居中显示
            this.getContentPane().add(digits[i]); // 添加标签到界面
        }

        // 创建一个停止按钮，用于停止所有线程
        JButton stop = new JButton("Stop");
        stop.addActionListener(new ActionListener() { // 为按钮添加事件监听器
            public void actionPerformed(ActionEvent e) {
                for (int i = 0; i < 5; i++) { // 遍历所有生成器
                    generators[i].stop(); // 调用生成器的 stop 方法停止线程
                }
            }
        });
        this.getContentPane().add(stop); // 添加按钮到界面

        // 设置窗口大小和属性
        this.setSize(600, 100); // 设置窗口大小
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE); // 设置关闭操作
        this.setVisible(true); // 设置窗口可见

        // 创建 5 个生成器线程并启动
        for (int i = 0; i < 5; i++) {
            generators[i] = new Generator(digits[i]); // 初始化生成器并绑定对应的标签
            Thread t = new Thread(generators[i]); // 创建新线程
            t.start(); // 启动线程
        }
    }

    /**
     * 主方法，程序入口点。
     * 使用 SwingUtilities.invokeLater 确保线程安全的 Swing 操作。
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new Question5Pro(); // 创建主窗口实例
            }
        });
    }
}

/**
 * 生成器类，实现 Runnable 接口，用于生成随机字符。
 */
class Generator implements Runnable {
    // 定义一个字符数组，包含 0-9 和 a-z
    private static final char[] CHARS = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z'
    };

    private volatile boolean running = true; // 标志位，用于控制线程的运行状态
    private JLabel target; // 目标标签，用于显示随机字符
    private Random random; // 随机数生成器

    /**
     * 构造方法，初始化目标标签和随机数生成器。
     *
     * @param target 要显示随机字符的 JLabel。
     */
    public Generator(JLabel target) {
        this.target = target; // 绑定目标标签
        random = new Random(System.currentTimeMillis()); // 初始化随机数生成器
    }

    /**
     * 停止方法，设置标志位为 false，停止线程。
     */
    public void stop() {
        running = false; // 设置标志位为 false
    }

    /**
     * 线程运行方法，不断生成随机字符并更新到目标标签。
     */
    public void run() {
        try {
            // 当标志位为 true 并且线程未被中断时，持续运行
            while (running && !Thread.interrupted()) {
                int next = random.nextInt(CHARS.length); // 随机生成一个字符的索引
                // 使用 SwingUtilities.invokeLater 确保线程安全的 Swing 操作
                SwingUtilities.invokeLater(new Runnable() {
                    public void run() {
                        target.setText("" + CHARS[next]); // 更新目标标签的文本
                    }
                });
                Thread.sleep(100); // 暂停线程 100 毫秒，降低字符切换速度
            }
        } catch (Exception e) {
            e.printStackTrace(); // 打印异常堆栈信息
        }
    }
}