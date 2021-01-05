/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab9_A
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 1010
using namespace std;
int road[MAXN][MAXN], n, m;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    cin >> T;
    for (int k = 1; k <= T; ++k)
    {
        memset(road, 0, sizeof(road));
        cin >> n >> m;
        for (int i = 0, st, ed; i < m; ++i)
            cin >> st >> ed, ++road[st][ed];
        for (int i = 1; i <= n; ++i, cout << endl)
            for (int j = 1; j <= n; ++j)
                cout << road[i][j] << " ";
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}