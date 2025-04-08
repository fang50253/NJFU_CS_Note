import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.awt.*;
public class Question5 extends JFrame{
    private JLabel digits[]=new JLabel[5];
    private Generator generators[]=new Generator[5];
    public Question5(){
        super();
        this.create();
    }
    private void create(){
        this.getContentPane().setLayout(new GridLayout(1,6));
        for(int i=0;i<5;i++){
            digits[i]=new JLabel();
            this.getContentPane().add(digits[i]);
        }
        JButton stop=new JButton();
        stop.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                for(int i=0;i<5;i++){
                    generators[i].stop();
                }
            }
        });
        this.getContentPane().add(stop);
        this.resize(600,100);
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        this.setVisible(true);
        for(int i=0;i<5;i++){
            generators[i]=new Generator(digits[i]);
            Thread t=new Thread(generators[i]);
            t.start();
        }
    }
    public static void main(String[] args){
        SwingUtilities.invokeLater(new Runnable(){
            public void run(){
                new Question5();
            }
        });
    }
}
class Generator implements Runnable{
    private static final char[] CHARS = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
    'u', 'v', 'w', 'x', 'y', 'z'
    };
    private volatile boolean running=true;
    private JLabel target;
    private Random random;
    public Generator(JLabel target){
        this.target=target;
        random=new Random(System.currentTimeMillis());
    }
    public void stop(){
        running=false;
    }
    public void run(){
        try{
            while(running&&!Thread.interrupted()){
                int next=random.nextInt(CHARS.length);
                SwingUtilities.invokeLater(new Runnable(){
                    public void run(){
                        target.setText(""+CHARS[next]);
                    }
                });
                Thread.sleep(1);
            }
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }
}