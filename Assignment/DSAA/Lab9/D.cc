/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab9_D
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
#define N 200007
#define M 500007
#define MX 2147483647
#define INF 0x3F3F3F3F
using namespace std;
struct edge_t
{
    int dat, len;
    edge_t *nxt;
} p[M + N];
struct node_t
{
    int dat, len;
    node_t(int x, int y) : dat(x), len(y) {}
    bool operator<(const node_t &x) const
    {
        return this->len > x.len;
    }
};
int n, m, dis[N], top;
inline void add_edge(int x, int y, int z)
{
    p[++top].dat = y, p[top].nxt = p[x].nxt, p[top].len = z, p[x].nxt = &p[top];
}
inline void dijkstra(int c)
{
    memset(dis, 0x3F, sizeof(dis));
    priority_queue<node_t> Q;
    Q.push(node_t(c, dis[c] = 0));
    while (!Q.empty())
    {
        node_t x = Q.top();
        Q.pop();
        if (x.len != dis[x.dat])
            continue;
        for (edge_t *k = p[x.dat].nxt; k != NULL; k = k->nxt)
            if (dis[k->dat] > dis[x.dat] + k->len)
            {
                dis[k->dat] = dis[x.dat] + k->len;
                Q.push(node_t(k->dat, dis[k->dat]));
            }
    }
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    top = n;
    for (int i = 0, x, y, z; i < m; ++i)
    {
        scanf("%d%d%d", &x, &y, &z);
        add_edge(x, y, z);
    }
    dijkstra(1);
    printf("%d ", dis[n] == INF ? -1 : dis[n]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}