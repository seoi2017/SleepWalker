/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_G
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 100010
#define MAXLGN 20
#define MOD 1000000007
using namespace std;
long long ans = 0LL;
int a[MAXN], b[MAXN], nxt[MAXN], pre[MAXN], pos[MAXN], totA[MAXN], totB[MAXN];
int rmq[MAXN][MAXLGN];
int n, k;
inline int getRMQ(int l, int r)
{
    int k = log2(r - l + 1);
    return max(rmq[l][k], rmq[r - (1 << k) + 1][k]);
}
inline long long solve(int x)
{
    long long ret = 0LL, temp = 0LL;
    int r1 = 0, r2 = 0;
    for (int i = x; i >= 0 && r1 <= k; i = pre[i])
        a[++r1] = i - pre[i], totA[r1] = totA[r1 - 1] + a[r1];
    for (int i = x; i <= n && r2 <= k; i = nxt[i])
        b[++r2] = nxt[i] - i, totB[r2] = totB[r2 - 1] + b[r2];
    for (int i = 1; i <= r1; ++i)
        if (k - i + 1 >= 1 && k - i + 1 <= r2)
        {
            if (a[i] == 0)
                continue;
            temp = (long long)a[i] * b[k - i + 1] % MOD;
            // printf("[%d %d]\n", x - totA[i], x + totB[k - i + 1]);
            // printf("Add: %lld, ", temp);
            temp = (temp * getRMQ(x - totA[i] + 1, x + totB[k - i + 1] - 1)) % MOD;
            // printf("AddT: %lld\n", temp);
            ret = (ret + temp) % MOD;
        }
    return ret;
}
inline void delPtr(int x)
{
    int nx = nxt[x];
    pre[nx] = pre[x];
    nxt[pre[x]] = nx;
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
        ans = 0LL;
        scanf("%d%d", &n, &k);
        memset(rmq, 0, sizeof(rmq));
        for (int i = 1, temp; i <= n; ++i)
        {
            pre[i] = i - 1;
            nxt[i] = i + 1;
            scanf("%d", &temp);
            pos[temp] = i;
            rmq[i][0] = temp;
        }
        for (int j = 1; j < MAXLGN; ++j)
            for (int i = 1; i + (1 << j) - 1 < MAXN; ++i)
                rmq[i][j] = max(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]);
        for (int i = 1; i <= n + 1; ++i)
        {
            ans = (ans + (solve(pos[i]) * i % MOD)) % MOD;
            delPtr(pos[i]);
        }
        printf("%lld\n", ans);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}