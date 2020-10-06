/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab2_A
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#define PMOD 1000000007
using namespace std;
int T;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d", &T);
    for (int i = 0; i < T; ++i)
    {
        long long n;
        scanf("%lld", &n);
        long long ans = (n * (n + 1) % PMOD) * (n * (n + 1) % PMOD) % PMOD * 250000002 % PMOD;
        printf("%lld\n", ans);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}