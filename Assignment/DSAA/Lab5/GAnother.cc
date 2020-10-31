// BZOJ 3956 AC
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 1000003
using namespace std;
int n, m, h[N], st[N], suml[N], sumr[N];
int f[20][N], cnt, mark[N], l[N], type;
struct data
{
    int x, y;
} point[N * 2];
int cmp1(data a, data b)
{
    return a.x < b.x;
}
int cmp2(data a, data b)
{
    return a.y > b.y;
}
void solve()
{
    for (int i = 1; i <= n; i++)
        f[0][i] = i;
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            if (j + (1 << i) - 1 <= n)
            {
                int x = f[i - 1][j];
                int y = f[i - 1][j + (1 << (i - 1))];
                if (h[x] < h[y])
                    f[i][j] = y;
                else
                    f[i][j] = x;
            }
    int j = 0;
    for (int i = 1; i <= n; i++)
    {
        if ((1 << (j + 1)) <= i)
            j++;
        l[i] = j;
    }
}
int calc(int x, int y)
{
    int k = l[y - x];
    int a = f[k][x];
    int b = f[k][y - (1 << k) + 1];
    if (h[a] < h[b])
        return b;
    else
        return a;
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    type = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &h[i]);
    int top = 1;
    st[top] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (h[i] < h[st[top]])
        {
            ++top;
            st[top] = i;
        }
        else
        {
            while (h[st[top]] <= h[i] && top)
            {
                ++cnt;
                point[cnt].x = st[top];
                point[cnt].y = i;
                if (h[st[top]] == h[i] && top != 1)
                    mark[i] = 1;
                if (top - 1 && !mark[st[top]])
                {
                    ++cnt;
                    point[cnt].x = st[top - 1];
                    point[cnt].y = st[top];
                }
                top--;
            }
            st[++top] = i;
        }
    }
    for (int i = top; i >= 2; i--)
        if (!mark[st[i]])
        {
            ++cnt;
            point[cnt].x = st[i - 1];
            point[cnt].y = st[i];
        }
    sort(point + 1, point + cnt + 1, cmp1);
    for (int i = 1; i <= cnt; i++)
        suml[point[i].x]++, sumr[point[i].y]++;
    for (int i = 1; i <= n; i++)
        suml[i] += suml[i - 1];
    for (int i = 1; i <= n; i++)
        sumr[i] += sumr[i - 1];
    solve();
    int lastans = 0;
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        if (type)
            l = (l + lastans - 1) % n + 1, r = (r + lastans - 1) % n + 1;
        if (l > r)
            swap(l, r);
        int t = calc(l, r);
        lastans = suml[t - 1] - suml[l - 1] + sumr[r] - sumr[t];
        printf("%d\n", lastans);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}