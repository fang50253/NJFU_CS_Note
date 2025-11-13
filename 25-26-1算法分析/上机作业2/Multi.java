import java.util.*;
public class Multi
{
    public static void matrixMultiply(int [][]a,int [][]b,int [][]c,int ra,int ca,int rb,int cb)
    {
        if(ca!=rb) throw new IllegalArgumentException("Error!!!");
        for(int i=0;i<ra;++i)
        {
            for(int j=0;j<cb;++j)
            {
                int sum=a[i][0]*b[0][j];
                for(int k=1;k<ca;++k) sum+=a[i][k]*b[k][j];
                c[i][j]=sum;
            }
        }
    }
    public static void matrixChain(int []p,int [][]m,int [][]s)
    {
        int n=p.length-1;
        for(int i=1;i<=n;++i) m[i][i]=0;
        for(int r=2;r<=n;++r)
        {
            for(int i=1;i<=n-r+1;++i)
            {
                int j=i+r-1;
                m[i][j]=m[i+1][j]+p[i-1]*p[i]*p[j];
                s[i][j]=i;
                for(int k=i+1;k<j;++k)
                {
                    int t=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                    if(t<m[i][j])
                    {
                        m[i][j]=t;
                        s[i][j]=k;
                    }
                }
            }
        }
    }
    public static void traceback(int [][]s,int i,int j)
    {
        if(i==j) return;
        traceback(s,i, s[i][j]);
        traceback(s,s[i][j]+1,j);
        System.out.println("Multiplay A"+i+","+s[i][j]+"and A"+(s[i][j]+1)+","+j);
    }
    // 主函数
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] p = new int[n+1];
        for(int i=0;i<=n;++i)
            p[i] = sc.nextInt();
        int[][] m = new int[n+1][n+1];
        int[][] s = new int[n+1][n+1];
        matrixChain(p, m, s);
        System.out.println(m[1][n]);
        traceback(s, 1, n);
    }
}