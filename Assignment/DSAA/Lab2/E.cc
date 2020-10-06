/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab2_E
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int n, T;
long long a[1000010];
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d", &T);
    a[1] = 1, a[2] = 1, a[3] = 1;
    for (int i = 4; i <= 1000000; ++i)
        a[i] = a[i / 2 - 1] + a[i / 2] + a[i / 2 + 1];
    while (T--)
    {
        scanf("%d", &n);
        printf("%lld\n", a[n]);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}