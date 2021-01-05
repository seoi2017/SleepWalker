/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab7_B
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <queue>
#define MAXN 100010
using namespace std;
long long n;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld", &n);
        long long node = 1LL, tot = 1LL;
        int height = 1;
        while (tot < n)
            tot += (node *= 2), ++height;
        printf("%d\n", height);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}