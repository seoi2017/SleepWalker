/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab7_F
*/
#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#define MAXN 100010
using namespace std;
int n, m, o;
int cnt;
int top;
int fa[MAXN], son[MAXN], sizeArray[MAXN], deep[MAXN], id[MAXN], ct[MAXN];
int seq[MAXN], que[MAXN], seqPtr, maxQue, ans;
bool visit[MAXN];
struct edge_t
{
    int dat;
    edge_t *nxt;
} e[(MAXN << 1) + MAXN];
inline void add_edge(int x, int y)
{
    edge_t *now = &e[++top];
    now->dat = y;
    now->nxt = e[x].nxt;
    e[x].nxt = now;
}
void dfs_1(int x, int f, int d)
{
    deep[x] = d, fa[x] = f;
    sizeArray[x] = 1;
    int maxson = -1, y;
    for (edge_t *k = e[x].nxt; k; k = k->nxt)
    {
        y = k->dat;
        if (y == f)
            continue;
        dfs_1(y, x, d + 1);
        sizeArray[x] += sizeArray[y];
        if (sizeArray[y] > maxson)
            son[x] = y, maxson = sizeArray[y];
    }
}
void dfs_2(int x, int chain_top)
{
    id[x] = ++cnt;
    ct[x] = chain_top;
    if (!son[x])
        return;
    dfs_2(son[x], chain_top);
    for (edge_t *k = e[x].nxt; k; k = k->nxt)
    {
        int y = k->dat;
        if (y == fa[x] || y == son[x])
            continue;
        dfs_2(y, y);
    }
}
inline int query(int x, int y)
{
    while (ct[x] != ct[y])
    {
        if (deep[ct[x]] < deep[ct[y]])
            swap(x, y);
        x = fa[ct[x]];
    }
    if (deep[x] < deep[y])
        return x;
    return y;
}
inline void getSeq(int x)
{
    visit[x] = true;
    for (edge_t *k = e[x].nxt; k; k = k->nxt)
    {
        if (visit[k->dat] == true)
            continue;
        seq[k->dat] = ++seqPtr;
        getSeq(k->dat);
    }
}
inline void init()
{
    cnt = top = 0;
    memset(fa, 0, sizeof(fa));
    memset(son, 0, sizeof(son));
    memset(sizeArray, 0, sizeof(sizeArray));
    memset(deep, 0, sizeof(deep));
    memset(id, 0, sizeof(id));
    memset(ct, 0, sizeof(ct));
    memset(visit, 0, sizeof(visit));
    memset(seq, 0, sizeof(seq));
    for (int i = 0; i <= n; ++i)
        e[i].dat = 0, e[i].nxt = nullptr;
    ans = 0, maxQue = 0;
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--)
    {
        scanf("%d%d", &n, &m);
        init();
        top = n, o = 1;
        for (int i = 1, x, y; i < n; ++i)
        {
            scanf("%d%d", &x, &y);
            add_edge(x, y);
            add_edge(y, x);
        }
        dfs_1(o, 0, 1);
        dfs_2(o, o);
        seq[1] = ++seqPtr;
        getSeq(o);
        for (int i = 1, x; i <= m; ++i)
        {
            scanf("%d", &que[i]);
            if (deep[que[i]] > deep[maxQue])
                maxQue = que[i];
        }
        // printf("%d\n", maxQue);
        for (int i = 1, lca; i <= m; ++i)
        {
            lca = query(que[i], maxQue);
            ans = max(ans, deep[que[i]] - deep[lca] + deep[maxQue] - deep[lca]);
            // printf("%d\n", ans);
        }
        printf("%d\n", (ans + 1) / 2);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}