/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab3_A
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define MAXN 200020
using namespace std;
int n, m;
int a[MAXN], b[MAXN];
void mergesort(int l, int r, int x[], int y[])
{
    if (l >= r)
        return;
    int mid = (l + r) >> 1;
    int ls = l, le = mid;
    int rs = mid + 1, re = r;
    mergesort(ls, le, x, y);
    mergesort(rs, re, x, y);
    int st = l;
    while (ls <= le && rs <= re)
        y[st++] = x[ls] < x[rs] ? x[ls++] : x[rs++];
    while (ls <= le)
        y[st++] = x[ls++];
    while (rs <= re)
        y[st++] = x[rs++];
    for (st = l; st <= r; ++st)
        x[st] = y[st];
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        memset(a, 0, sizeof(a));
        for (int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        for (int i = n; i < n + m; ++i)
            scanf("%d", &a[i]);
        mergesort(0, n + m - 1, a, b);
        for (int i = 0; i < n + m; ++i)
            printf("%d ", a[i]);
        printf("\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}