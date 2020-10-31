/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_C
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 2010
using namespace std;
long long n, m;
struct Pair
{
    long long key, value;
    Pair(long long x = 0LL, long long y = 0LL): key(x), value(y) {}
    bool operator<=(const Pair x) const
    {
        return this->key <= x.key;
    }
}mp[MAXN], temp[MAXN];
template<class T>
void mergesort(int l, int r, T x[], T y[])
{
    if (l >= r)
        return;
    int mid = (l + r) >> 1;
    int ls = l, le = mid;
    int rs = mid + 1, re = r;
    mergesort(ls, le, x, y);
    mergesort(rs, re, x, y);
    int st = l;
    while (ls <= le && rs <= re)
        y[st++] = x[ls] <= x[rs] ? x[ls++] : x[rs++];
    while (ls <= le)
        y[st++] = x[ls++];
    while (rs <= re)
        y[st++] = x[rs++];
    for (st = l; st <= r; ++st)
        x[st] = y[st];
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    long long T;
    scanf("%lld", &T);
    while (T--)
    {
        long long temp1, temp2;
        scanf("%lld", &n);
        for (long long i = 0; i < n; ++i)
        {
            scanf("%lld%lld", &temp1, &temp2);
            mp[i].key = temp2, mp[i].value = temp1;
        }
        scanf("%lld", &m);
        for (long long j = 0; j < m; ++j)
        {
            scanf("%lld%lld", &temp1, &temp2);
            mp[n + j].key = temp2, mp[n + j].value = temp1;
        }
        mergesort(0, n + m - 1, mp, temp);
        bool allZero = true;
        long long key = 0LL, value = 0LL;
        for (int i = 0; i < n + m; ++i)
        {
            key = mp[i].key, value = mp[i].value;
            while (mp[i + 1].key == mp[i].key && i + 1 < n + m)
                value += mp[++i].value;
            if (value == 0)
                continue;
            allZero = false;
            if (key == 0)
            {
                printf("%lld", value);
                continue;
            }
            if (value > 0 && key != mp[0].key)
                printf("+");
            if (value == 1LL);
            else if (value == -1LL)
                printf("-");
            else
                printf("%lld", value);            
            printf("x");
            if (key != 1)
                printf("^%lld", key);
        }
        if (allZero == true)
            printf("0");
        printf("\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}