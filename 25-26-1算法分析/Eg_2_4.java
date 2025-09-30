public class Eg_2_4 {
    public static void perm(Object[] list, int k, int m) {
        if (k == m) {
            for (int i = 0; i <= m; ++i) {
                System.out.print(list[i] + " ");
            }
            System.out.println();
        } else {
            for (int i = k; i <= m; ++i) {
                swap(list, k, i);
                perm(list, k + 1, m);
                swap(list, k, i);
            }
        }
    }

    public static void swap(Object[] list, int i, int j) {
        Object tmp = list[i];
        list[i] = list[j];
        list[j] = tmp;
    }

    public static void main(String[] args) {
        Object[] list = new Object[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        perm(list,3,5);
    }
}