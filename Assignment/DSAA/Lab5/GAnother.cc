/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab5_G
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 300010
#define MAXLGN 20
using namespace std;
struct Node
{
    int val, ind;
    Node(int x = 0, int y = 0): val(x), ind(y) {}
    bool operator<(const Node &x) const
    {
        return this->val < x.val;
    }
};
struct Ask
{
    int l, r, index;
    long long result;
    Ask(int x = 0, int y = 0, int index = 0) : l(x), r(y), index(index)
    {
        this->result = 0LL;
    }
}ask[MAXN];
class Stack
{
private:
    int cnt;
    Node array[MAXN];
public:
    Stack(): cnt(0) {}
    Node top()
    {
        if (this->isEmpty() == false)
            return this->array[this->cnt - 1];
        return Node(0, 0);
    }
    bool isEmpty()
    {
        return this->cnt == 0 ? true : false;
    }
    bool pop()
    {
        if (this->isEmpty() == true)
            return false;
        --this->cnt;
        return true;
    }
    void push(const int &x, const int &y)
    {
        this->array[this->cnt++] = Node(x, y);
    }
    int searchIndex(const int &pos)
    {
        int l = 0, r = this->cnt, mid;
        while (l < r)
        {
            mid = (l + r) >> 1;
            if (array[mid].ind < pos)
                l = mid + 1;
            else
                r = mid;
        }
        return this->array[l].ind;
    }
    void clear()
    {
        this->cnt = 0;
    }
}stack;
int n, q, val[MAXN], sumL[MAXN], sumR[MAXN];
inline void debugOutput()
{
    printf("L: ");
    for (int i = 1; i <= n; ++i)
        printf("%d ", sumL[i]);
    printf("\nR: ");
    for (int i = 1; i <= n; ++i)
        printf("%d ", sumR[i]);
    printf("\n");
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d%d", &n ,&q);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &val[i]);
    for (int i = 1; i <= n; ++i)
    {
        while (stack.isEmpty() == false && stack.top().val <= val[i])
        {
            if (stack.top().val != val[i])
                ++sumR[i];
            stack.pop();
        }
        stack.push(val[i], i);
    }
    for (int i = 1; i <= n; ++i)
        sumR[i] += sumR[i - 1];
    stack.clear();
    for (int i = n; i > 0; --i)
    {
        while (stack.isEmpty() == false && stack.top().val <= val[i])
        {
            if (stack.top().val != val[i])
                ++sumL[i];
            stack.pop();
        }
        stack.push(val[i], i);
    }
    for (int i = n; i > 0; --i)
        sumL[i] += sumL[i + 1];
    stack.clear();
    for (int i = 0; i < q; ++i)
    {
        scanf("%d%d", &ask[i].l, &ask[i].r);
        ask[i].index = i;
    }
    sort(ask, ask + q, [](const Ask &x, const Ask &y) { return x.r < y.r; });
    for (int i = 0, maxPos; i < q; ++i)
    {
        for (int j = (i == 0 ? 1 : ask[i - 1].r + 1); j <= ask[i].r; ++j)
        {
            while (stack.isEmpty() == false && val[j] > stack.top().val)
                stack.pop();
            stack.push(val[j], j);
        }
        maxPos = stack.searchIndex(ask[i].l);
        ask[i].result += sumL[ask[i].l] - sumL[maxPos];
        ask[i].result += sumR[ask[i].r] - sumR[maxPos];
        ask[i].result += (ask[i].r - ask[i].l);
    }
    // debugOutput();
    sort(ask, ask + q, [](const Ask &x, const Ask &y) { return x.index < y.index; });
    for (int i = 0; i < q; ++i)
        printf("%lld\n", ask[i].result);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}