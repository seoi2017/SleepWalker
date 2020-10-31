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
}rmq[MAXN][MAXLGN];
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
    void clear()
    {
        this->cnt = 0;
    }
}stack;
class Tree
{
private:
    int array[MAXN];
    inline int lowbit(const int &x)
    {
        return x & -x;
    }
public:
    Tree()
    {
        memset(this->array, 0, sizeof(this->array));
    }
    void change(int pos, int val)
    {
        for (int i = pos; i <= MAXN; i += this->lowbit(i))
            array[i] += val;
    }
    long long getSum(int pos)
    {
        long long ans = 0LL;
        for (int i = pos; i > 0; i -= this->lowbit(i))
            ans += (long long)array[i];
        return ans;
    }
}treeL, treeR;
int n, q, val[MAXN];
long long ans;
inline int getPosRMQ(int l, int r)
{
    int k = log2(r - l + 1);
    return max(rmq[l][k], rmq[r - (1 << k) + 1][k]).ind;
}
inline void buildRMQ()
{
    for (int j = 1; j < MAXLGN; ++j)
        for (int i = 1; i + (1 << j) - 1 < MAXN; ++i)
            rmq[i][j] = max(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]);
}
inline void debugOutput()
{
    printf("L: ");
    for (int i = 1; i <= n; ++i)
        printf("%lld ", treeL.getSum(n - i + 1));
    printf("\nR: ");
    for (int i = 1; i <= n; ++i)
        printf("%lld ", treeR.getSum(i));
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
    {
        scanf("%d", &val[i]);
        rmq[i][0] = Node(val[i], i);
    }
    buildRMQ();
    for (int i = 1; i <= n; ++i)
    {
        while (stack.isEmpty() == false && stack.top().val <= val[i])
        {
            if (stack.top().val != val[i])
                treeR.change(i, 1);
            stack.pop();
        }
        stack.push(val[i], i);
    }
    stack.clear();
    for (int i = n; i > 0; --i)
    {
        while (stack.isEmpty() == false && stack.top().val <= val[i])
        {
            if (stack.top().val != val[i])
                treeL.change(n - i + 1, 1);
            stack.pop();
        }
        stack.push(val[i], i);
    }
    // debugOutput();
    for (int i = 0, askL, askR, maxPos; i < q; ++i)
    {
        scanf("%d%d", &askL, &askR);
        ans = 0LL;
        maxPos = getPosRMQ(askL, askR);
        ans += treeL.getSum(n - askL + 1) - treeL.getSum(n - maxPos + 1);
        ans += treeR.getSum(askR) - treeR.getSum(maxPos);
        ans += (askR - askL);
        printf("%lld\n", ans);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}