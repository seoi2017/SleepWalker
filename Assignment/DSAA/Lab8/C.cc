/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab8_C
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 100010
using namespace std;
int n, fa[MAXN];
struct Node
{
    int value, limit;
    bool operator<(const Node& other) const
    {
        return this->value > other.value;
    }
}node[MAXN];
long long ans;
int findfa(const int& x)
{
    if (fa[x] == -1)
        return x;
    return fa[x] = findfa(fa[x]);
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    cin >> T;
    while(T--)
    {
        cin >> n;
        memset(fa, -1, sizeof(fa));
        for (int i = 0; i < n; ++i)
            cin >> node[i].value;
        for (int i = 0; i < n; ++i)
            cin >> node[i].limit;
        sort(node, node + n);
        ans = 0LL;
        for (int i = 0, k; i < n; ++i)
        {
            k = findfa(node[i].limit);
            if (k > 0)
                ans += (long long)node[i].value, fa[k] = k - 1;
        }
        cout << ans << endl;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}