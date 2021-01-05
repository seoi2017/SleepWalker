/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab9_C
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
int n, m, inDeg[MAXN];
vector<int> edge[MAXN];
priority_queue<int, vector<int>, greater<int>> q;
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
        edge[st].push_back(ed);
        ++inDeg[ed];
    }
    for (int i = 1; i <= n; ++i)
        if (inDeg[i] == 0)
            q.push(i);
    while (q.empty() == false)
    {
        int ptr = q.top();
        q.pop();
        cout << ptr << " ";
        inDeg[ptr] = -1;
        for (int nxt : edge[ptr])
            if(--inDeg[nxt] == 0)
                q.push(nxt);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}