/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab7_C
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <vector>
#define MAXN 100010
using namespace std;
int n;
vector<int> node[MAXN];
queue<int> q;
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
        for (int i = 0; i <= n; ++i)
            node[i].clear();
        for (int i = 2, to; i <= n; ++i)
        {
            cin >> to;
            node[to].push_back(i);
        }
        q.push(1);
        cout << 1 << " ";
        while (q.empty() == false)
        {
            int now = q.front();
            q.pop();
            for (int i : node[now])
            {
                q.push(i);
                cout << i << " ";
            }
        }
        cout << endl;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}