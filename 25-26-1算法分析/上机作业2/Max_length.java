
import java.util.Scanner;

public class Max_length
{
    public static int N=1010;
    public static int n,m;
    public static int lcsLength(char []x,char[]y,int [][]b)
    {
        int [][]c=new int[m+1][n+1];
        for(int i=0;i<=m;++i) c[i][0]=0;
        for(int i=0;i<=n;++i) c[0][i]=0;
        for(int i=1;i<=m;++i)
        {
            for(int j=1;j<=n;++j)
            {
                if(x[i]==y[j])
                {
                    c[i][j]=c[i-1][j-1]+1;
                    b[i][j]=1;
                }
                else if(c[i-1][j]>=c[i][j-1])
                {
                    c[i][j]=c[i-1][j];
                    b[i][j]=2;
                }
                else
                {
                    c[i][j]=c[i][j-1];
                    b[i][j]=3;
                }
            }
        }
        return c[m][n];
    }
    public static void lcs(int i,int j,char[] x,int [][]b)
    {
        if(i==0||j==0) return;
        if(b[i][j]==1)
        {
            lcs(i-1,j-1,x,b);
            System.out.print(x[i]);
        }
        else if(b[i][j]==2) lcs(i-1,j,x,b);
        else lcs(i,j-1,x,b);
    }
    public static void main(String[] args)
    {
        Scanner scanner=new Scanner(System.in);
        n=scanner.nextInt();
        m=scanner.nextInt();
        scanner.nextLine();
        String xStr = scanner.nextLine();
        String yStr = scanner.nextLine();
        char[] x = new char[N];
        char[] y = new char[N];
        for(int i = 0; i < xStr.length(); i++) x[i + 1] = xStr.charAt(i);
        for(int i = 0; i < yStr.length(); i++) y[i + 1] = yStr.charAt(i);
        int[][] b = new int[N][N];
        int maxLength = lcsLength(x, y, b);
        System.out.println("LCS Length Matrix:");
        for(int i = 1; i <= m; ++i) 
        {
            for(int j = 1; j <= n; ++j)  System.out.print(b[i][j] + " ");
            System.out.println();
        }
        System.out.println("Max lcsLength=" + maxLength);
        System.out.print("LCS: ");
        lcs(m, n, x, b);
        System.out.println();
        scanner.close();
    }
}