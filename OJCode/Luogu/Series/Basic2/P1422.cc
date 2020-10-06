/*
Author: Invrise
OJ Site: Luogu
Problem ID: P1422
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    double c1 = 0.4463, c2 = 0.4663, c3 = 0.5663;
    int po;
    double ans = 0;
    cin >> po;
    if (po >= 401)
        ans += (po - 400) * c3;
    if (po >= 151)
        ans += min(250, po - 150) * c2;
    ans += min(po, 150) * c1;
    cout << fixed << setprecision(1) << ans << endl;
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}