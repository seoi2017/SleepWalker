/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_F
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXLEN 210010
#define BLOCK 450
using namespace std;
struct Node
{
    char sub[BLOCK * 2 + 10];
    int size;
    Node *prev, *next;
}block[BLOCK];
int blockNum = 0;
inline void init(const char *str)
{
    blockNum = 0;
    Node *last = &block[blockNum++], *node;
    while (strlen(str) > 0)
    {
        int len = min((int)strlen(str), BLOCK);
        node = &block[blockNum++];
        node->prev = last;
        last->next = node;
        node->size = len;
        memcpy(node->sub, str, len * sizeof(char));
        str = str + len;
        last = node;
    }
}
inline void insert(char c, int pos)
{
    Node *node = block[0].next;
    while (node->next != nullptr && pos > node->size)
    {
        pos -= node->size;
        node = node->next;
    }
    --pos;
    for (int i = node->size; i > pos; --i)
        node->sub[i] = node->sub[i - 1];
    node->sub[pos] = c;
    if (++node->size >= BLOCK * 2)
    {
        Node *step = &block[blockNum++];
        memcpy(step->sub, node->sub + BLOCK, BLOCK);
        node->size -= BLOCK;
        step->size = BLOCK;
        step->next = node->next;
        step->prev = node;
        node->next->prev = step;
        node->next = step;
    }
}
inline char query(int pos)
{
    Node *node = block[0].next;
    while (pos > node->size)
    {
        pos -= node->size;
        node = node->next;
    }
    return node->sub[--pos];
}
char str[MAXLEN], chr;
int n;
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
        scanf("%s", str);
        init(str);
        scanf("%d", &n);
        for (int i = 0, oper; i < n; ++i)
        {
            scanf("%d ", &oper);
            if (oper == 1)
            {
                scanf("%c%d", &chr, &oper);
                insert(chr, oper);
            }
            else
            {
                scanf("%d", &oper);
                printf("%c\n", query(oper));
            }
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}