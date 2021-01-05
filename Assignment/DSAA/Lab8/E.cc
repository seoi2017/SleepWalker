/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab8_E
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 100010
using namespace std;
using BigInt = long long;
template<typename T, int MaxSize>
class Treap
{
private:
    struct Node
    {
        T key;
        int lc, rc, size, prioroty;
    }node[MaxSize];
    int count, root;

    inline int random()
    {
        return rand() % 0x7FFFFFFF;
    }

    inline void pushUp(int ptr)
    {
        if (ptr != 0)
            node[ptr].size = node[node[ptr].lc].size + node[node[ptr].rc].size + 1;
    }
public:
    Treap() : count(0), root(0)
    {
        srand(time(0));
    }

    int create(T key)
    {
        int ptr = ++count;
        node[ptr].key = key;
        node[ptr].size = 1;
        node[ptr].lc = 0;
        node[ptr].rc = 0;
        node[ptr].prioroty = random();
        return ptr;
    }

    void split(int ptr, int key, int& x, int& y)
    {
        if (ptr == 0)
        {
            x = 0, y = 0;
            return;
        }
        if (key >= node[ptr].key)
            x = ptr, split(node[ptr].rc, key, node[ptr].rc, y);
        else
            y = ptr, split(node[ptr].lc, key, x, node[ptr].lc);
        pushUp(ptr);
    }

    int merge(int x, int y)
    {
        if (x == 0 || y == 0)
            return x + y;
        if (node[x].prioroty > node[y].prioroty)
        {
            node[x].rc = merge(node[x].rc, y);
            pushUp(x);
            return x;
        }
        else
        {
            node[y].lc = merge(x, node[y].lc);
            pushUp(y);
            return y;
        }
    }

    void insert(T key)
    {
        int x, y;
        split(root, key - 1, x, y);
        root = merge(merge(x, create(key)), y);
    }

    void remove(T key)
    {
        int x, y, z;
        split(root, key, x, z);
        split(x, key - 1, x, y);
        if (y != 0)
            y = merge(node[y].lc, node[y].rc);
        root = merge(merge(x, y), z);
    }

    int rank(T key)
    {
        int x, y, result;
        split(root, key - 1, x, y);
        result = node[x].size + 1;
        root = merge(x, y);
        return result;
    }

    T value(int rank)
    {
        int ptr = root;
        while (true)
        {
            if (node[node[ptr].lc].size + 1 == rank)
                break;
            else if (node[node[ptr].lc].size + 1 > rank)
                ptr = node[ptr].lc;
            else
            {
                rank -= (node[node[ptr].lc].size + 1);
                ptr = node[ptr].rc;
            }
        }
        return node[ptr].key;
    }

    T prev(T key)
    {
        int x, y, ptr;
        T result;
        split(root, key - 1, x, y);
        ptr = x;
        while (node[ptr].rc != 0)
            ptr = node[ptr].rc;
        result = node[ptr].key;
        root = merge(x, y);
        return result;
    }

    T next(T key)
    {
        int x, y, ptr;
        T result;
        split(root, key, x, y);
        ptr = y;
        while (node[ptr].lc != 0)
            ptr = node[ptr].lc;
        result = node[ptr].key;
        root = merge(x, y);
        return result;
    }

    int size()
    {
        return node[root].size;
    }

    bool find(T key)
    {
        int x, y, z;
        split(root, key, x, z);
        split(x, key - 1, x, y);
        bool result;
        if (node[y].size > 0)
            result = true;
        else
            result = false;
        root = merge(merge(x, y), z);
        return result;
    }
};
Treap<BigInt, MAXN> tree;
BigInt m, k, val[MAXN];
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    cin >> m >> k;
    for (int i = 1; i <= m; ++i)
        cin >> val[i];
    for (int i = 1; i <= k; ++i)
        tree.insert(val[i]);
    for (int i = k, temp; i <= m; ++i)
    {
        cin >> temp;
        cout << tree.value(temp) << endl;
        tree.remove(val[i - k + 1]);
        tree.insert(val[i + 1]);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}