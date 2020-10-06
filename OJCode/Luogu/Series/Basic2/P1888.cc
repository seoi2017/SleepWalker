/*
Author: Invrise
OJ Site: Luogu
Problem ID: P1888
*/
#include <bits/stdc++.h>
using namespace std;
int gcd(int x, int y)
{
    return x % y == 0 ? y : gcd(y, x % y);
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int a[] = {0, 0, 0}, tmp;
    cin >> a[0] >> a[1] >> a[2];
    sort(a, a + 3);
    while ((tmp = gcd(a[0], a[2])) != 1)
    {
        a[0] /= tmp;
        a[2] /= tmp;
    }
    cout << a[0] << "/" << a[2] << endl;
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}