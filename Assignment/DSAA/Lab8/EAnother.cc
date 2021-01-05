/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab8_E
*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define MAXN 200010
#define INF 0x3F3F3F3F
using namespace std;
int num[MAXN], sorted[MAXN], root[MAXN], cnt;
struct Node
{
    int sum, l, r;
    Node(const int& _sum = 0, const int& _l = 0, const int& _r = 0) : sum(_sum), l(_l), r(_r) {}
} node[MAXN << 5];
void insert(int &root, int pos, int l, int r)
{
    node[++cnt] = Node(node[root].sum + 1, node[root].l, node[root].r);
    root = cnt;
    if (l == r)
        return;
    int m = (l + r) >> 1;
    if (pos <= m)
        insert(node[root].l, pos, l, m);
    else
        insert(node[root].r, pos, m + 1, r);
}
int query(int stPtr, int edPtr, int l, int r, int k)
{
    if (l == r)
        return l;
    int m = (l + r) >> 1;
    int sum = node[node[edPtr].l].sum - node[node[stPtr].l].sum;
    if (k <= sum)
        return query(node[stPtr].l, node[edPtr].l, l, m, k);
    else
        return query(node[stPtr].r, node[edPtr].r, m + 1, r, k - sum);
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int n, m, tot, pos, Node;
    scanf("%d%d", &n, &m);
    cnt = 0;
    root[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &num[i]);
        sorted[i] = num[i];
    }
    sort(sorted + 1, sorted + n + 1);
    tot = unique(sorted + 1, sorted + 1 + n) - (sorted + 1);
    for (int i = 1; i <= n; i++)
    {
        root[i] = root[i - 1];
        pos = lower_bound(sorted + 1, sorted + tot + 1, num[i]) - sorted;
        insert(root[i], pos, 1, tot);
    }
    int l = 1, r = m, k;
    for (int i = r; i <= n; ++i)
    {
        scanf("%d", &k);
        pos = query(root[l - 1], root[r], 1, tot, k);
        printf("%d\n", sorted[pos]);
        ++l, ++r;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}