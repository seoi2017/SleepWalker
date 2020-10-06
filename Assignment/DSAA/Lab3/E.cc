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
}ls[MAXN];
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
        sort(ls, ls + n);
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