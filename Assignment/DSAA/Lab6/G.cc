/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab6_G
*/
#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <map>
#define MAXN 100010
#define MOD 998244353
#define HASH 131
using namespace std;
using ULL_T = unsigned long long;
map<ULL_T, int> hashMap;
string str[MAXN];
int n, nextArray[MAXN * 10], total[MAXN * 10];
ULL_T pre, val, ans;
inline void getHash(const string &s, const int &ind)
{
    pre = 1ULL, val = 0ULL;
    for (int i = s.length() - 1; i >= 0; --i)
    {
        val += (s[i] - 'a' + 1) * pre;
        pre *= HASH;
        hashMap[val] += ind;
    }
}
inline void getNext(const string &s)
{
    nextArray[0] = -1;
    int i = 0, j = -1;
    while (i < s.length())
        if (j == -1 || s[j] == s[i])
            nextArray[++i] = ++j;
        else
            j = nextArray[j];
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0, len; i < n; ++i)
    {
        cin >> str[i];
        getHash(str[i], i + 1);
    }
    ans = 0ULL;
    for (int i = 0, len; i < n; ++i)
    {
        val = 0ULL, len = str[i].length();
        for (int j = 0; j < len; ++j)
        {
            val = val * HASH + str[i][j] - 'a' + 1;
            total[j + 1] = hashMap[val];
        }
        getNext(str[i]);
        for (int j = 1; j <= len; ++j)
            total[nextArray[j]] -= total[j];
        for (int j = 1; j <= len; ++j)
            ans = (ans + (((ULL_T)j * total[j] % MOD) * (i + 1) % MOD)) % MOD;
    }
    cout << ans << endl;
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}