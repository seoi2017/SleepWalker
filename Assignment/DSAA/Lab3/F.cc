/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab3_F
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define MAXN 200020
#define EPS 1e-8
using namespace std;
int n, x, y;
double p, q;
struct Line
{
    int ind;
    double high;
    bool operator<(const Line &x) const
    {
        return this->high < x.high || (this->high == x.high && this->ind < x.ind);
    }
}lp[MAXN], lq[MAXN];
template<class T>
void quicksort(int l, int r, T x[])
{
    T mid = x[(l + r) >> 1];
    int i = l, j = r;
    while (i <= j)
    {
        while (x[i] < mid)
            ++i;
        while (mid < x[j])
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
    scanf("%d%d%d", &n, &x, &y);
    p = (double)x + EPS;
    q = (double)y - EPS;
    for (int i = 0, k, b; i < n; ++i)
    {
        scanf("%d%d", &k, &b);
        lp[i].ind = i;
        lp[i].high = (double)k * p + b;
        lq[i].ind = i;
        lq[i].high = (double)k * q + b;
    }
    quicksort(0, n - 1, lq);
    quicksort(0, n - 1, lp);
    bool can = false;
    for (int i = 0; i < n; ++i)
        if (lq[i].ind != lp[i].ind)
        {
            can = true;
            printf("YES");
            break;
        }
    if (can == false)
        printf("NO");
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}