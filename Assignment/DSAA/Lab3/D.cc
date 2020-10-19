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
    bool operator<=(const Number &x) const
    {
        return this->val <= x.val;
    }
}b[MAXN], c[MAXN];
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
        y[st++] = x[ls] <= x[rs] ? x[ls++] : x[rs++];
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
        mergesort(0, n - 1, b, c);
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