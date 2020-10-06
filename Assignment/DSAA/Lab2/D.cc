/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab2_D
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#define N 100010
using namespace std;
int n, m, L, a[N], p[N];
inline bool solve(int target)
{
    int cnt = 0, l = 0, r = 1;
    for (int val = 0; l < r && r <= n; ++r)
    {
        if (a[r] - a[r - 1] > target)
            return false;
        val += (a[r] - a[r - 1]);
        if (val > target)
        {
            ++cnt;
            if (cnt > m)
                return false;
            val -= (a[r - 1] - a[l]);
            l = r - 1;
        }
    }
    if (a[n] - a[l] > target || cnt + 1 > m)
        return false;
    else
        return true;
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &L);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
    }
    a[n] = L;
    memset(p, 0, sizeof(p));
    int l = 0, r = L;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (solve(mid) == true)
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", r == L ? -1 : r);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}