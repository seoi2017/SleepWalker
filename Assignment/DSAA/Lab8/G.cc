/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab8_G
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#define MAXN 100010
using namespace std;
using BigInt = long long;
using Item = pair<int, int>;
vector<Item> node[MAXN];
int n, value[MAXN], fa[MAXN];
BigInt ans = 0LL;
auto cmp = [](const Item& x, const Item& y) -> bool
{
    if (x.first == y.first)
        return x.second < y.second;
    return x.first < y.first;
};
auto clear = [](vector<Item>& x) -> void
{
    x.clear();
};
int init(const int& x)
{
    if (node[x].empty() == true)
        return 1;
    for (auto& i : node[x])
        i.first = init(i.second);
    sort(node[x].begin(), node[x].end(), cmp);
    return node[x].back().first + 1;
}

int dpWork(const int& x, const int& deep, const int& val)
{
    value[x] = val;
    if (node[x].empty() == true)
        return 1;
    int result = val;
    for (auto i : node[x])
        result = min(deep, dpWork(i.second, deep + 1, result + 1));
    return result + 1;
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for_each(node + 1, node + n + 1, clear);
        for (int i = 2; i <= n; ++i)
        {
            cin >> fa[i];
            node[fa[i]].push_back(make_pair(0, i));
        }
        init(1);
        dpWork(1, 0, 0);
        ans = 0LL;
        for (int i = 1; i <= n; ++i)
            if (node[i].empty() == true)
                ans += (BigInt)value[i];
        cout << ans << endl;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}