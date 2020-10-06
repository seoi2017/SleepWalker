/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab2_G
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#define N 100010
#define MXL 1000000007
using namespace std;
typedef long long ll_t;
ll_t T, n, K, M, a[N];
inline ll_t judge(ll_t target)
{
    ll_t tot = 0, cnt = 0, ans = 0;
    for (int i = 0; i < n; ++i)
    {
        while (cnt < K && tot < n)
            if (a[tot++] >= target)
                ++cnt;
        if (cnt < K)
            return ans;
        if (a[i] >= target)
            --cnt;
        ans += (n - tot + 1);
    }
    return ans;
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld%lld%lld", &n, &K, &M);
        for (int i = 0; i < n; ++i)
        {
            scanf("%lld", &a[i]);
        }
        ll_t l = 1, r = MXL, mid;
        while (l < r)
        {
            mid = (l + r + 1) >> 1;
            if (judge(mid) >= M)
                l = mid;
            else
                r = mid - 1;
        }
        printf("%lld\n", l);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}