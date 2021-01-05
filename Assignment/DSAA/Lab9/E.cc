/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab9_E
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
using BigInt = long long;
BigInt sp = 0LL, tp = 0LL;
int n, m, s, t, sDist[MAXN], tDist[MAXN];
vector<int> edge[MAXN];
queue<int> sq, tq;
bool sVisit[MAXN], tVisit[MAXN];
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    cin >> n >> m >> s >> t;
    for (int i = 0, st, ed; i < m; ++i)
        cin >> st >> ed, edge[ed].push_back(st), edge[st].push_back(ed);
    sq.push(s);
    while (sq.empty() == false)
    {
        int ptr = sq.front();
        sq.pop(), sVisit[ptr] = true;
        for (int nxt : edge[ptr])
            if (nxt != t && sVisit[nxt] == false)
                sq.push(nxt);
    }
    tq.push(t);
    while (tq.empty() == false)
    {
        int ptr = tq.front();
        tq.pop(), tVisit[ptr] = true;
        for (int nxt : edge[ptr])
            if (nxt != s && tVisit[nxt] == false)
                tq.push(nxt);
    }
    for (int i = 1; i <= n; ++i)
        if (sVisit[i] == true && tVisit[i] == false)
            ++sp;
        else if (sVisit[i] == false && tVisit[i] == true)
            ++tp;
        else
            continue;
    /*
    for (int i = 1; i <= n; ++i)
        cout << i << " " << sVisit[i] << " " << tVisit[i] << endl;
    */
    cout << (sp - 1LL) * (tp - 1LL) << endl;
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}