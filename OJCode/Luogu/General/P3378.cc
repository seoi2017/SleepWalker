/*
Author: Invrise
OJ Site: Luogu
Problem ID: P3369
*/
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1000010;
int heap[MAXN], top = 0, n, ope, val;
inline void insert(const int& x)
{
    heap[++top] = x;
    int now = top, nxt;
    while (now > 1)
    {
        nxt = now >> 1;
        if (heap[now] >= heap[nxt])
            return;
        swap(heap[now], heap[nxt]);
        now = nxt;
    }
}
inline void remove()
{
    swap(heap[1], heap[top--]);
    int now = 1, nxt;
    while ((now << 1) <= top)
    {
        nxt = now << 1;
        if (nxt < top && heap[nxt + 1] < heap[nxt])
            ++nxt;
        if (heap[now] <= heap[nxt])
            return;
        swap(heap[now], heap[nxt]);
        now = nxt;
    }
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d", &n);
    while (n--)
    {
        switch (scanf("%d", &ope), ope)
        {
        case 1:
            scanf("%d", &val);
            insert(val);
            break;
        case 2:
            printf("%d\n", heap[1]);
            break;
        case 3:
            remove();
            break;
        default:
            break;
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}