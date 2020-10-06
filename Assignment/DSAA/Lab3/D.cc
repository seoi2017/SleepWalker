/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab3_D
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define MAXN 100020
using namespace std;
int n;
int tree[MAXN];
struct Number
{
    int val, ind;
    bool operator<(const Number &x) const
    {
        return this->val < x.val;
    }
}b[MAXN];
inline int lowbit(int x)
{
    return x&(-x);
}
inline void update(int i, int x)
{
    while (i <= n)
    {
        tree[i] += x;
        i += lowbit(i);
    }
}
inline long long getAns(int i)
{
    long long ans = 0;
    while (i > 0)
    {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
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
        scanf("%d", &n);
        memset(tree, 0, sizeof(tree));
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &b[i].val);
            b[i].ind = i + 1;
        }
        stable_sort(b, b + n);
        long long cnt = 0LL;
        for (int i = 0; i < n; ++i)
        {
            cnt += i - getAns(b[i].ind); 
            update(b[i].ind, 1);
        }
        printf("%lld\n", cnt);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}