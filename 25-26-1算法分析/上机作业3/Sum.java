import java.util.*;
public class Sum
{
    public static int N=110;
    public static int[] x=new int[N];
    public static int n,sum;//长度信息
    public static void output(int[] p)
    {
        int ans=0;
        for(int i=0;i<n;++i) ans+=x[i]*(i+1);
        //if(ans!=sum) return;
        System.out.print("[");
        for(int i=0;i<n-1;++i)
        {
            if(x[i]==1) System.out.print((i+1)+",");
        }
        System.out.print("]");
    }
    public static boolean constraint(int t)
    {
        int ans=0;
        for(int i=0;i<n;++i) ans+=x[i]*(i+1);
        //System.out.println("[Debug]"+ans);
        return ans<sum;
    } 
    public static boolean bound(int t)
    {
        return t<n;
    }
    public static void backtrace(int t)
    {
        if(t>n) output(x);
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
        n=sc.nextInt();
        sum=sc.nextInt();
        System.err.print("[");
        backtrace(0);
        System.err.print("]");
    }
}