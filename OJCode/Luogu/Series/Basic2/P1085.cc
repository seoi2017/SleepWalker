/*
Author: Invrise
OJ Site: Luogu
Problem ID: P1085
*/
#include <bits/stdc++.h>
#define rep(x, y, z) for (int x = y; x <= z; ++x)
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int ans = 0, val = 8;
    rep(i, 1, 7)
    {
        int a, b;
        cin >> a >> b;
        if (a + b > val)
        {
            val = a + b;
            ans = i;
        }
    }
    cout << ans << endl;
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}