/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab2_F
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MXN 100010
#define MX_TIME 0x3F3F3F3F3F3F3F3F
using namespace std;
typedef long long ll_t;
ll_t xTo, yTo, xBe, yBe, dx, dy, n;
char opec[MXN];
int *ope[MXN];
int dirs[4][2] = {
    {0, 1}, // U
    {0, -1}, // D
    {1, 0}, //R
    {-1, 0} //L
};
inline ll_t judge(ll_t val)
{
    ll_t xD = xTo, yD = yTo;
    xD += dx * (val / n);
    yD += dy * (val / n);
    for (int i = 0; i < val % n; ++i)
    {
        xD += ope[i][0];
        yD += ope[i][1];
    }
    return val - (abs(xBe - xD) + abs(yBe - yD));
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%lld%lld%lld%lld", &xTo, &yTo, &xBe, &yBe);
    scanf("%lld", &n);
    scanf("%s", opec);
    for (int i = 0; i < n; ++i)
    {
        switch (opec[i])
        {
        case 'U':
            ope[i] = dirs[0];
            break;
        case 'D':
            ope[i] = dirs[1];
            break;
        case 'R':
            ope[i] = dirs[2];
            break;
        case 'L':
            ope[i] = dirs[3];
            break;
        default:
            break;
        }
        dx += ope[i][0];
        dy += ope[i][1];
    }
    // printf("%lld, %lld\n", dx, dy);
    ll_t l = 0, r = MX_TIME;
    while (l < r)
    {
        ll_t mid = (l + r) >> 1;
        if (judge(mid) >= 0)
            r = mid;
        else
            l = mid + 1;
    }
    printf("%lld\n", r == MX_TIME ? -1 : r);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}