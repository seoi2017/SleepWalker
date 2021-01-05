/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab9_G
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#define MAXN 100010
#define MOD 1000000007
using namespace std;
using BigInt = long long;
int n, m, a[MAXN], b[MAXN];
BigInt dp[MAXN];
vector<int> node[MAXN];
BigInt solve(const int& ptr)
{
    if (dp[ptr] != 0LL)
        return dp[ptr];
    BigInt result = 0LL, subResult;
    for (int nxt : node[ptr])
    {
        subResult = solve(nxt);
        if (node[nxt].empty() == false)
            result = (result + subResult) % MOD;
        result = (result + b[nxt]) % MOD;
    }
    return dp[ptr] = result;
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
        cin >> n >> m;
        for (int i = 1; i <= n; ++i)
            cin >> a[i] >> b[i], dp[i] = 0LL, node[i].clear();
        for (int i = 0, st, ed; i < m; ++i)
        {
            cin >> st >> ed;
            node[st].push_back(ed);
        }
        BigInt result = 0LL;
        for (int i = 1; i <= n; ++i)
            result = (result + (solve(i) * a[i]) % MOD) % MOD;
        cout << result << endl;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}