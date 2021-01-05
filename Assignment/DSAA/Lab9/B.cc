/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab9_B
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
#define MAXN 100010
using namespace std;
int n, m, deg[MAXN];
vector<int> node[MAXN];
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 0, st, ed; i < m; ++i)
    {
        cin >> st >> ed;
        node[st].push_back(ed);
        node[ed].push_back(st);
        ++deg[st], ++deg[ed];
    }
    queue<int> q;
    beginTag:
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 1)
            q.push(i);
    if (q.empty() == true)
        goto endTag;
    while (q.empty() == false)
    {
        --deg[q.front()];
        for (int nxt : node[q.front()])
            --deg[nxt];
        q.pop();
    }
    goto beginTag;
    endTag:
    bool result = true;
    for (int i = 1; i <= n; ++i)
        if (deg[i] > 1)
            result = false;
    cout << (result ? "Good" : "Bad") << endl;
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}