/*
Author: Invrise
OJ Site: Luogu
Problem ID: P1909
*/
#include <bits/stdc++.h>
#define MAXN 0x3F3F3F3F
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int target, ans = MAXN;
    cin >> target;
    for (int i = 1, a, b, tmp; i <= 3; ++i)
    {
        cin >> a >> b;
        tmp = (target / a + (target % a > 0 ? 1 : 0)) * b;
        ans = min(ans, tmp);
    }
    cout << ans;
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}