/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab3_E
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define MAXN 200020
using namespace std;
long long n, p, q;
struct Lushi
{
    long long hp, atk, benefit;
    bool operator<(const Lushi &x) const
    {
        return this->benefit > x.benefit;
    }
}ls[MAXN], tp[MAXN];
template<class T>
void mergesort(int l, int r, T x[], T y[])
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
    scanf("%lld%lld%lld", &n, &p, &q);
    long long ans1 = 0LL, ans2 = 0LL, ans = 0LL;
    for (int i = 0; i < n; ++i)
    {
        scanf("%lld%lld", &ls[i].hp, &ls[i].atk);
        ls[i].benefit = max(0LL, ls[i].hp - ls[i].atk);
        ans1 += ls[i].atk;
    }
    if (q == 0LL)
        printf("%lld", ans1);
    else
    {
        mergesort(0, n - 1, ls, tp);
        q = min(q, n);
        for (int i = 0; i < q; ++i)
            ans2 += ls[i].benefit;
        for (int i = 0; i < n; ++i)
        {
            ans = max(ans, ans2 - ls[i < q ? i : (q - 1)].benefit + (ls[i].hp << p) - ls[i].atk);
        }
        printf("%lld", ans1 + ans);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}