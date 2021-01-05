/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab9_F
*/
#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
#define MAXN 50010
using namespace std;
using BigInt = long long;
BigInt n, m, q, k, query[MAXN], result[MAXN], grandQ;
struct Edge
{
    BigInt to, len;
    Edge(const BigInt& to, const BigInt& len) : to(to), len(len) {}
};
struct Node
{
    BigInt from, to, pos, len;
    Node(const BigInt& from, const BigInt& to, const BigInt& pos, const BigInt& len) : from(from), to(to), pos(pos), len(len) {}
    bool operator<(const Node& other) const
    {
        return this->len > other.len;
    }
};
vector<Edge> edge[MAXN];
priority_queue<Node> que;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    auto cmp = [](const Edge& a, const Edge& b) -> bool
    {
        return a.len < b.len;
    };
    auto init = [&]() -> void
    {
        scanf("%lld%lld%lld", &n, &m ,&q); // cin >> n >> m >> q;
        grandQ = 0LL, k = 0LL;
        for (int i = 0; i <= n; ++i)
            edge[i].clear();
        for (BigInt i = 0, st, ed, len; i < m; ++i)
            scanf("%lld%lld%lld", &st, &ed, &len)/* cin >> st >> ed >> len */, edge[st].push_back({ed, len});
        for (int i = 0; i < q; ++i)
            scanf("%lld", &query[i])/* cin >> query[i] */, grandQ = max(grandQ, query[i]);
        for (int i = 1; i <= n; ++i)
        {
            sort(edge[i].begin(), edge[i].end(), cmp);
            if (edge[i].size() > 0)
                que.push({i, edge[i][0].to, 0, edge[i][0].len});
        }
    };
    auto solve = [&]() -> void
    {
        while (que.empty() == false)
        {
            Node ptr = que.top();
            que.pop(), result[++k] = ptr.len;
            if (grandQ == k)
            {
                while (que.empty() == false)
                    que.pop();
                break;
            }
            if (edge[ptr.to].size() > 0)
                que.push({ptr.to, edge[ptr.to][0].to, 0, ptr.len + edge[ptr.to][0].len});
            if (ptr.pos + 1 < edge[ptr.from].size())
                que.push({ptr.from, edge[ptr.from][ptr.pos + 1].to, ptr.pos + 1, ptr.len - edge[ptr.from][ptr.pos].len + edge[ptr.from][ptr.pos + 1].len});
        }
    };
    int T;
    scanf("%d", &T); // cin >> T;
    while (T--)
    {
        init(), solve();
        for (int i = 0; i < q; ++i)
            printf("%lld\n", result[query[i]]); // cout << result[query[i]] << endl;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}