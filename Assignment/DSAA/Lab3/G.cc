/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab3_G
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define MAXN 300020
using namespace std;
long long n, m, a[MAXN], b[MAXN];
template<class T>
void quicksort(int l, int r, T x[])
{
    T mid = x[(l + r) >> 1];
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
    if (j > l)
        quicksort(l, j, x);
    if (i < r)
        quicksort(i, r, x);
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    for (int i = 0; i < n; ++i)
        scanf("%lld", &a[i]);
    for (int i = n - 1; i >= 0; --i)
        b[i] = b[i + 1] + a[i];
    quicksort(1, n - 1, b);
    long long ans = b[0];
    for (int i = n - 1; i > n - m; --i)
        ans += b[i];
    printf("%lld", ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}