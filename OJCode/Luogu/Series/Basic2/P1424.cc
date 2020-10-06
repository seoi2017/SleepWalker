/*
Author: Invrise
OJ Site: Luogu
Problem ID: P1424
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int x, n, ans = 0;
    cin >> x >> n;
    for (int i = 1, t = x; i <= n; ++i, ++t)
    {
        t %= 7;
        if (t == 0 || t == 6)
            continue;
        ans += 250;
    }
    cout << ans << endl;
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}