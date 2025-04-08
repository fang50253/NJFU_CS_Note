import java.util.*;
public class P1010{
    public void fff(int x){
        for(int i=14;i;--i){
            if(pow(2,i)<=x){
                if(==0) System.out.print("2(0)");
                else if(x==1) System.out.print("2");
                else{
                    System.out.print("2(");
                    fff(i);
                    System.out.print(")");
                }
                x-=pow(2,i);
            }
        }
    }
    public static void main(String[] args){
        Scanner scanner=new Scanner(System.in);
        int n=scanner.nextInt();
        fff(n);
    }
}