/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab2_B
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#define NMAX 100010
using namespace std;
int N, T, a[NMAX];
int solve(int x)
{
    int l = 0, r = N + 1;
    while (r - l > 1)
    {
        int mid = (l + r) >> 1;
        if (a[mid] > x)
        {
            r = mid;
            continue;
        }
        else if (a[mid] < x)
        {
            l = mid;
            continue;
        }
        else
        {
            return -1;
        }
    }
    return x - a[l];
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d%d", &N, &T);
    a[0] = 0;
    for (int i = 1; i <= N; ++i)
    {
        scanf("%d", &a[i]);
    }
    a[N + 1] = 1000000007;
    for (int i = 0, tmp; i < T; ++i)
    {
        scanf("%d", &tmp);
        tmp = solve(tmp);
        if (tmp == -1)
        {
            printf("Accept\n");
        }
        else
        {
            printf("%d\n", tmp);
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}