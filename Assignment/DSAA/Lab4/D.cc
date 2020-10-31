/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_D
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 300010
using namespace std;
struct Node
{
    Node *prev, *next;
    int val, pos;
    bool operator<(const Node &x) const
    {
        return this->val < x.val;
    }
}data[MAXN], *midPtr;
int n, ans[MAXN / 2], top, pos[MAXN];
inline void erase(Node *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
}
inline void print()
{
    for (Node *it = data[0].prev; it != nullptr; it = it->next)
        printf("%d ", it->val);
    printf("\n");
}
void quicksort(int l, int r, Node x[])
{
    Node mid = x[(l + r) >> 1];
    int i = l, j = r;
    while (i <= j)
    {
        while (x[i] < mid)
            ++i;
        while (mid < x[j])
            --j;
        if (i <= j)
        {
            swap(x[i], x[j]);
            ++i, --j;
        }
    }
    if (j > l)
        quicksort(l, j, x);
    if (i < r)
        quicksort(i, r, x);
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
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &data[i].val);
            if (i == n - 1 && n % 2 == 0)
            {
                --n;
                break;
            }
            data[i].pos = i;
        }
        quicksort(0, n - 1, data);
        for (int i = 0; i < n; ++i)
        {
            data[i].prev = (i == 0 ? new Node() : &data[i - 1]);
            data[i].next = (i == n - 1 ? new Node() : &data[i + 1]);
            pos[data[i].pos] = i;
            data[i].pos = i;
        }
        data[0].prev->next = &data[0];
        data[n - 1].next->prev = &data[n - 1];
        midPtr = &data[n / 2];
        ans[top++] = midPtr->val;
        for (int i = n - 1; i > 0; i -= 2)
        {
            if (pos[i] >= midPtr->pos && pos[i - 1] >= midPtr->pos)
                midPtr = midPtr->prev;
            else if (pos[i] <= midPtr->pos && pos[i - 1] <= midPtr->pos)
                midPtr = midPtr->next;
            ans[top++] = midPtr->val;
            erase(&data[pos[i]]);
            erase(&data[pos[i - 1]]);
            // print();
        }
        while (top > 0)
            printf("%d ", ans[--top]);
        printf("\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}