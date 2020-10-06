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
    sort(lq, lq + n);
    sort(lp, lp + n);
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