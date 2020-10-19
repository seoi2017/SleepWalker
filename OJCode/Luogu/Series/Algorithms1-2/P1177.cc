/*
Author: Invrise
OJ Site: Luogu
Problem ID: P1177
*/
#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 100010;
void quicksort(int l, int r, int x[])
{
    int mid = x[(l + r) >> 1];
    int i = l, j = r;
    while (i <= j)
    {
        while (x[i] < mid)
            ++i;
        while (x[j] > mid)
            --j;
        if (i <= j)
        {
            swap(x[i], x[j]);
            ++i, --j;
        }
    }
    #pragma omp parallel sections
    {
        #pragma omp section
        if (j > l)
        {
            quicksort(l, j, x);
        }
        #pragma omp section
        if (i < r)
        {
            quicksort(i, r, x);
        }
    }
}
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
        y[st++] = x[ls] < x[rs] ? x[ls++] : x[rs++]; // 这里使用小于等于则为稳定排序，使用小于则为不稳定排序
    while (ls <= le)
        y[st++] = x[ls++];
    while (rs <= re)
        y[st++] = x[rs++];
    for (st = l; st <= r; ++st)
        x[st] = y[st];
}
int n, a[maxn], b[maxn];
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    quicksort(0, n - 1, a);
    // mergesort(0, n - 1, a, b);
    for (int i = 0; i < n; ++i)
        printf("%d ", a[i]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}