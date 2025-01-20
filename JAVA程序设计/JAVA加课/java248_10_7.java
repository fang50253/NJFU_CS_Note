import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class java248_10_7 extends JFrame {
    private JLabel[] labels = new JLabel[6];  // 6 个标签
    private Thread[] threads = new Thread[6]; // 每个标签对应一个线程
    private boolean running = true;          // 控制线程是否运行

    public java248_10_7() {
        // 设置窗口标题、布局和关闭操作
        setTitle("数字变化程序");
        setLayout(new GridLayout(2, 3, 10, 10)); // 网格布局：2 行 3 列
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(400, 200);

        // 创建标签并添加到窗口中
        for (int i = 0; i < labels.length; i++) {
            labels[i] = new JLabel("0", SwingConstants.CENTER); // 标签默认显示 "0"
            labels[i].setFont(new Font("Arial", Font.BOLD, 30)); // 设置字体和大小
            labels[i].setBorder(BorderFactory.createLineBorder(Color.BLACK));
            add(labels[i]);
        }

        // 创建并启动每个标签对应的线程
        for (int i = 0; i < threads.length; i++) {
            final int index = i; // 保存索引供线程使用
            threads[i] = new Thread(() -> {
                while (true) {
                    if (!running) break; // 如果运行标志为 false，退出线程
                    int randomNum = (int) (Math.random() * 10); // 生成随机数字 0～9
                    labels[index].setText(String.valueOf(randomNum)); // 更新标签
                    try {
                        Thread.sleep(500); // 每隔 500 毫秒更新一次
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt(); // 恢复中断状态
                        break;
                    }
                }
            });
            threads[i].start(); // 启动线程
        }

        // 创建 "停止" 按钮
        JButton stopButton = new JButton("停止");
        stopButton.setFont(new Font("Arial", Font.BOLD, 20));
        stopButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                running = false; // 设置运行标志为 false
            }
        });

        // 添加按钮到窗口
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(stopButton);
        add(buttonPanel);

        // 显示窗口
        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(java248_10_7::new); // 启动程序
    }
}