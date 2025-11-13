import java.util.*;
public class Sum_2
{
    public static int N=110;
    public static boolean flag=false;
    public static int[] x=new int[N];
    public static int n,sum,num_cnt;//长度信息
    public static boolean output(int[] p)
    {
        int cnt=0,ans=0;
        for(int i=1;i<=9;++i)
        {
            if(p[i]==1)
            {
                ++cnt;
                ans+=i;
            }
        }
        if(cnt!=num_cnt) return false;
        if(sum!=ans) return false;
        if(flag==true) System.out.print(",");
        System.out.print("[");
        for(int i=1;i<=9;++i)
        {
            if(p[i]==1)
            {
                if((--cnt!=0))System.out.print(i+",");
                else System.out.print(i+"]");
            }
        }
        return true;
    }
    public static boolean constraint(int t)
    {
        return true;
    }
    public static boolean bound(int t)
    {
        return t<=n;
    }
    public static void backtrace(int t)
    {
        if(t>n)
        {
            if(output(x)==true) flag=true;
        }
        else 
        {
            for(int i=0;i<=1;++i)
            {
                x[t]=i;
                if(constraint(t)&&bound(t)) backtrace(t+1);
            }
        }
    }
    public static void main(String []args)
    {
        Scanner sc=new Scanner(System.in);
        n=9;//只能选择1～9这9个数字
        num_cnt=sc.nextInt();
        sum=sc.nextInt();
        System.out.print("[");
        backtrace(1);
        System.out.print("]");
    }
}