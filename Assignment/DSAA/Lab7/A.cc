/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab7_A
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
long long n, m;
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
        cin >> n >> m;
        long long node = 1LL, tot = 1LL;
        while (tot <= n)
            tot += (node *= m);
        // cout << tot << endl;
        cout << node - (tot - n) + (tot - n) / m << endl;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}