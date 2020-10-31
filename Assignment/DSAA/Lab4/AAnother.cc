/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_A
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 131073
#define MAXPOW 17
using namespace std;
int n, k, maxNode;
int tree[MAXN];
inline int lowbit(int x)
{
    return x & (-x);
}
inline void change(int t, int x)
{
    for (int i = t; i <= maxNode; i += lowbit(i))
        tree[i] += x;
}
inline int query(int x)
{
    int ans = 0, now = 0;
    for (int i = 17; i >= 0; --i)
    {
        ans += (1 << i);
        if (maxNode < ans || tree[ans] + now >= x)
            ans -= (1 << i);
        else
            now += tree[ans];
    }
    return ans + 1;
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
        scanf("%d%d", &n, &k);
        memset(tree, 0, sizeof(tree));
        maxNode = n;
        for (int i = 1; i <= n; ++i)
            tree[i] = lowbit(i);
        int now = 1;
        while (n)
        {
            now = (now - 1 + k - 1) % n + 1;
            int ans = query(now);
            change(ans, -1);
            printf("%d ", ans);
            --n;
        }
        printf("\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}