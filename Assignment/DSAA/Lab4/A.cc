/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_A
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 131073
using namespace std;
struct Node
{
    int val;
    Node *prev, *next;
}pool[MAXN];
int n, k, top;
Node *it;
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
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i)
        {
            pool[i].val = i;
            pool[i].next = &pool[i + 1];
            pool[i].prev = &pool[i - 1];
        }
        pool[n].next = &pool[1];
        pool[1].prev = &pool[n];
        it = &pool[1];
        top = 0;
        while (n != 0)
        {
            if (++top == k)
            {
                it->prev->next = it->next;
                it->next->prev = it->prev;
                printf("%d ", it->val);
                if (it->next == it)
                    break;
                top = 0;
            }
            it = it->next;
        }
        printf("\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}