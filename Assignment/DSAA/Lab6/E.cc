/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab6_E
*/
#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#define MAXN 100010
using namespace std;
using ULL_T = unsigned long long;
constexpr int hashKey = 131;
string a, b;
ULL_T hashMap[MAXN];
int cnt = 0;
inline void init(const int &x)
{
    ULL_T pre = 1ULL, hashVal = 0ULL;
    int len = a.length();
    cnt = 0;
    for (register int i = 0; i < x; ++i)
    {
        pre *= hashKey;
        hashVal = hashVal * hashKey + a[i];
    }
    hashMap[cnt++] = hashVal;
    for (register int i = x; i < len; ++i)
    {
        hashVal = hashVal * hashKey + a[i] - pre * a[i - x];
        hashMap[cnt++] = hashVal;
    }
    sort(hashMap, hashMap + cnt);
}
inline bool judge(const int &x)
{
    ULL_T pre = 1ULL, hashVal = 0ULL;
    for (register int i = 0; i < x; ++i)
    {
        pre *= hashKey;
        hashVal = hashVal * hashKey + b[i];
    }
    if (binary_search(hashMap, hashMap + cnt, hashVal))
        return true;
    for (register int i = x; i < b.length(); ++i)
    {
        hashVal = hashVal * hashKey + b[i] - pre * b[i - x];
        if (binary_search(hashMap, hashMap + cnt, hashVal))
            return true;
    }
    return false;
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    cin >> a >> b;
    int lenA = a.length();
    int lenB = b.length();
    int l = 0, r = min(lenA, lenB), mid;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        init(mid);
        if (judge(mid) == true)
            l = mid + 1;
        else
            r = mid - 1;
    }
    printf("%d\n", r);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}