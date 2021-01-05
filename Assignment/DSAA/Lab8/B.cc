/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab8_B
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 100010
using namespace std;
int n, m, value[MAXN], top;
pair<int, int> heap[MAXN];
inline void insert(const int& x, const int& y)
{
    heap[++top].first = x;
    heap[top].second = y;
    int ptr = top;
    while (ptr != 1 && heap[ptr] > heap[ptr >> 1])
    {
        swap(heap[ptr], heap[ptr >> 1]);
        ptr >>= 1;
    }
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        memset(heap, 0, sizeof(heap));
        top = 0;
        for (int i = 1; i <= n; ++i)
        {
            cin >> value[i];
            insert(value[i], i);
        }
        cin >> m;
        for (int i = 1, deep = 0, cnt; i <= n; ++i)
            if (heap[i].second == m)
            {
                cnt = i;
                while (cnt > 0)
                    cnt >>= 1, ++deep;
                cout << deep << " " << (i - (1 << (deep - 1)) + 1) << endl;
                break;
            }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}