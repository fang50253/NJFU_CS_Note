#include <cstdio>
const int MAXN = 200005;
int a[MAXN], b[MAXN];

int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n, m;
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &a[i]);
        }

        for (int i = 0; i < m; ++i)
        {
            scanf("%d", &b[i]);
        }

        int i = 0, j = 0;

        while (i < n && j < m)
        {
            if (a[i] >= b[j])
            {
                ++j;
            }
            ++i;
        }

        if (j == m)
        {
            printf("0\n");
        }
        else
        {
            int need = b[j];
            ++j; // 假设种了一朵美丽值为 b[j] 的花

            while (i < n && j < m)
            {
                if (a[i] >= b[j])
                {
                    ++j;
                }
                ++i;
            }

            if (j == m)
            {
                printf("%d\n", need);
            }
            else
            {
                printf("-1\n");
            }
        }
    }

    return 0;
}