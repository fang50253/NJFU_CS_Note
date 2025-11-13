public class QuickSort
{
    public static int N=10010;
    public static int a[]=new int[N];
    public static void swap(int[] arr, int i, int j)
    {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    public static int[] qsort(int p,int r)
    {
        if(p<r)
        {
            int q=partition(p,r);
            qsort(p,q-1);
            qsort(q+1,r);
        }
        return a;
    }
    public static int partition(int p,int r)
    {
        int i=p,j=r+1;
        int x=a[p];
        while(true)
        {
            while (a[++i]<x&&i<r);
            while (a[--j]>x);
            if(i>=j) break;
            swap(a,i,j);
        }
        a[p]=a[j];
        a[j]=x;
        return j;
    }
    public static void main(String[] args)
    {
        int[] Array = {1,5,3,8,6,2};
        System.arraycopy(Array,0,a,0,Array.length);
        qsort(0,Array.length-1);
        for(int i=0;i<Array.length;++i) System.out.print(a[i]+" ");
        System.out.println(" ");
    }
}