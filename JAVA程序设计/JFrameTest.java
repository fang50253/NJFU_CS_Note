import java.awt.*;
import javax.swing.*;
public class JFrameTest{
    public static void main(String args[]){
        JFrame jf=new JFrame();
        jf.setSize(1000,1000);
        jf.setLocation(400,250);
        jf.setTitle("I'm Fangzeyu");
        jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        JDialog jd=new JDialog(jf,"I'm Fangzeyu2");
        jd.setBounds(400,300,200,200);
        jd.setVisible(true);
        jd.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        JButton jb1=new JButton("bottom1");
        JButton jb2=new JButton("bottom2");
        JPanel jp=new JPanel(new FlowLayout());
        jp.add(jb1);
        jp.add(jb2);
        jf.add(jp);
        JLabel lb=new JLabel("user",SwingConstants.CENTER);
        jf.add(lb);
        jf.setVisible(true);
    }
}