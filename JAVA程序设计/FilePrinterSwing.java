import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

public class FilePrinterSwing extends JFrame {
    private JButton printFilesButton; // 按钮
    private JTextArea outputArea;     // 输出区域

    public FilePrinterSwing() {
        // 设置窗口标题
        setTitle("Recursive File Printer");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(600, 500);
        setLocationRelativeTo(null);

        // 初始化按钮
        printFilesButton = new JButton("Print Files");
        printFilesButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                printFiles();
            }
        });

        // 初始化文本区域
        outputArea = new JTextArea();
        outputArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(outputArea);

        // 布局设置
        setLayout(new BorderLayout());
        add(printFilesButton, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
    }

    private void printFiles() {
        // 指定的目录路径 (请修改为实际路径)
        String directoryPath = "/Users/fang50253/Desktop";
        File directory = new File(directoryPath);

        // 清空输出区域
        outputArea.setText("");

        if (directory.exists() && directory.isDirectory()) {
            // 调用递归函数
            listFilesRecursively(directory, "");
        } else {
            outputArea.append("Directory does not exist or is not a valid directory.\n");
        }
    }

    private void listFilesRecursively(File directory, String indent) {
        // 获取目录下的所有文件和子目录
        File[] files = directory.listFiles();

        if (files != null) {
            for (File file : files) {
                if (file.isFile()) {
                    // 输出文件路径
                    outputArea.append(indent + file.getAbsolutePath() + "\n");
                } else if (file.isDirectory()) {
                    // 输出目录路径并递归调用
                    outputArea.append(indent + "[Directory] " + file.getAbsolutePath() + "\n");
                    listFilesRecursively(file, indent + "    "); // 缩进子目录内容
                }
            }
        }
    }

    public static void main(String[] args) {
        // 启动程序
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new FilePrinterSwing().setVisible(true);
            }
        });
    }
}