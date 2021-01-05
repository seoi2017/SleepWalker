/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab6_C
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 1010
using namespace std;
int n, m, ans, nextArray[MAXN * 2];
string str[MAXN], ope, temp;
inline void findNext(const string &s)
{
    int len = s.length();
    nextArray[0] = -1;
    int k = -1, t = 0;
    while (t < len)
    {
        if (k == -1 || s[k] == s[t])
            nextArray[++t] = ++k;
        else
            k = nextArray[k];
    }
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> str[i];
    }
    cin >> m;
    ans = 0;
    for (int i = 0, ans1, ans2, sLen, tLen, s, t; i < m; ++i)
    {
        cin >> s >> t >> ope;
        sLen = str[--s].length();
        tLen = str[--t].length();
        temp = str[s] + str[t];
        findNext(temp);
        ans1 = nextArray[sLen + tLen];
        while (ans1 > tLen || ans1 > sLen)
            ans1 = nextArray[ans1];
        temp = str[t] + str[s];
        findNext(temp);
        ans2 = nextArray[tLen + sLen];
        while (ans2 > tLen || ans2 > sLen)
            ans2 = nextArray[ans2];
        switch (ope[0])
        {
        case '<':
            ans += (ans1 < ans2 ? 1 : 0);
            break;
        case '>':
            ans += (ans1 > ans2 ? 1 : 0);
            break;
        case '=':
            ans += (ans1 == ans2 ? 1 : 0);
            break;
        default:
            break;
        }
    }
    cout << ans;
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}