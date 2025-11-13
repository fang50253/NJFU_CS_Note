public class MergeSort
{
    public static int N=10010;
    public static int a[]=new int[N];
    public static int b[]=new int[N];
    public static int[] mergesort(int[] q,int left,int right)
    {
        if(left<right)
        {
            int i=left+right>>1;
            mergesort(a, left, i);
            mergesort(a, i+1, right);
            merge(a,b,left,i,right);
            copy(a,b,left,right);
        }
        return a;
    }
    public static void merge(int[] c,int[] d,int l,int m,int r)
    {
        int i=l,j=m+1,k=l;
        while((i<=m)&&j<=r)
        {
            if(c[i]<c[j]) d[k++]=c[i++];
            else d[k++]=c[j++];
        }
        if(i>m)
        {
            for(int q=j;q<=r;++q)
            {
                d[k++]=c[q];
            }
        }
        else
        {
            for(int q=i;q<=m;++q)
            {
                d[k++]=c[q];
            }
        }
    }
    public static void copy(int[] a,int[] b,int l,int r)
    {
        for(int i = l; i <= r; i++) a[i] = b[i];
    }
    public static void main(String[] args)
    {
        int[] Array = {1,5,3,8,6,2};
        System.arraycopy(Array,0,a,0,Array.length);
        mergesort(a,0,Array.length-1);
        for(int i=0;i<Array.length;++i) System.out.print(a[i]+" ");
        System.out.println(" ");
    }
}