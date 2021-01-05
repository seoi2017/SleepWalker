/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab8_F
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define INF 0x3F3F3F3F3F3F3F3F
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

Treap<BigInt, MAXN> adopters, pets;
BigInt n, oper, value, ans = 0LL;

inline BigInt getAns(Treap<BigInt, MAXN>& tree, BigInt value)
{
    if (tree.find(value) == true)
    {
        tree.remove(value);
        return 0LL;
    }
    BigInt pre = tree.prev(value), nxt = tree.next(value);
    pre = pre == 0LL ? INF : pre;
    nxt = nxt == 0LL ? INF : nxt;
    if (abs(pre - value) <= abs(nxt - value))
    {
        tree.remove(pre);
        return abs(pre - value);
    }
    else
    {
        tree.remove(nxt);
        return abs(nxt - value);
    }
}

int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    cin >> n;
    while (n--)
    {
        cin >> oper >> value;
        switch (oper)
        {
        case 0:
            if (adopters.size() > 0)
                ans += getAns(adopters, value);
            else
                pets.insert(value);
            break;
        case 1:
            if (pets.size() > 0)
                ans += getAns(pets, value);
            else
                adopters.insert(value);
            break;
        default:
            break;
        }
    }
    cout << ans << endl;
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}