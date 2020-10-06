/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab2_C
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#define N 3010
using namespace std;
long long n, S, t[N], ans = 0;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%lld%lld", &n, &S);
    for (int i = 0; i < n; ++i)
    {
        scanf("%lld", &t[i]);
    }
    ans = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1, temp; j < n - 1; ++j)
        {
            temp = (S - t[i] - t[j]);
            temp = upper_bound(t + j + 1, t + n, temp) - lower_bound(t + j + 1, t + n, temp);
            ans += temp;
        }
    }
    printf("%lld", ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}