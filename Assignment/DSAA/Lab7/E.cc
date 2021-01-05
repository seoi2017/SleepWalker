/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab7_E
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <queue>
#define MAXN 100010
using namespace std;
using ll_t = long long;
int n, cnt[MAXN];
ll_t ans, t1, t2;
queue<ll_t> q1, q2;
inline ll_t getValue()
{
    ll_t result;
    if (q2.empty() == true || (q1.empty() == false && q1.front() < q2.front()))
        result = q1.front(), q1.pop();
    else
        result = q2.front(), q2.pop();
    return result;
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    // T = 1;
    while (T--)
    {
        scanf("%d", &n);
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1, temp; i <= n; ++i)
        {
            scanf("%d", &temp);
            ++cnt[temp];
        }
        while (q1.empty() == false)
            q1.pop();
        while (q2.empty() == false)
            q2.pop();
        for (int i = 1; i <= 100000; ++i)
            for (int j = 1; j <= cnt[i]; ++j)
                q1.push((ll_t)i);
        ans = 0LL;
        for (int i = 1; i < n; ++i)
        {
            t1 = getValue(), t2 = getValue();
            ans += (ll_t)t1 + t2;
            q2.push((ll_t)t1 + t2);
        }
        printf("%lld\n", ans);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}