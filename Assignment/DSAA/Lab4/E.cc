/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_E
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 100010
#define MINN -100010
using namespace std;
struct Node
{
    int val;
    Node *prev, *next;
}pool[MAXN], *nxt[MAXN];
int n, topOpe, topNxt;
struct Interval
{
    Node *first, *second;
    Interval(Node *x = nullptr, Node *y = nullptr): first(x), second(y) {}
}ope[MAXN];
inline void scan()
{
    Node *summit = &pool[0], *last = &pool[0];
    for (Node *it = &pool[0]; it != nullptr; it = it->next)
    {
        if (it->val >= last->val)
        {
            if (summit != last)
                ope[topOpe++] = Interval(summit, last);
            summit = it;
        }
        last = it;
    }
}
inline void rescan()
{
    Node *node, *it;
    for (int i = 0; i < topNxt; ++i)
    {
        node = nxt[i];
        for (it = nxt[i]; it->next->val < it->val; it = it->next)
            if (i < topNxt - 1 && it == nxt[i + 1])
                ++i;
        if (node == it)
            continue;
        ope[topOpe++] = Interval(node, it);
    }
    topNxt = 0;
}
inline void solve()
{
    Node *begin, *end;
    for (int i = 0; i < topOpe; ++i)
    {
        begin = ope[i].first;
        end = ope[i].second;
        begin->prev->next = end->next;
        end->next->prev = begin->prev;
        if (topNxt > 0 && nxt[topNxt - 1] == begin->prev)
            continue;
        nxt[topNxt++] = begin->prev;
    }
    topOpe = 0;
}
inline void print()
{
    for (Node *it = &pool[0]; it != nullptr; it = it->next)
        if (it->val != MAXN && it->val != MINN)
            printf("%d ", it->val);
    printf("\n");
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
        pool[0].val = MINN;
        pool[0].prev = nullptr;
        pool[0].next = &pool[1];
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &pool[i].val);
            pool[i].prev = &pool[i - 1];
            pool[i].next = &pool[i + 1];
        }
        pool[n + 1].val = MAXN;
        pool[n + 1].prev = &pool[n];
        pool[n + 1].next = nullptr;
        scan();
        while (topOpe > 0)
        {
            solve();
            rescan();
        }
        print();
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}