/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab6_G
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <map>
#define MOD 998244353
using namespace std;
multimap<int, string> hashMapHead;
multimap<string, int> hashMapTail;
map<int, int> visit;
int n, last;
string str;
long long ans = 0LL;
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
        str.clear();
        cin >> str;
        for (auto it = str.begin() + 1; true; ++it)
        {
            hashMapHead.insert(make_pair(i + 1, string(str.begin(), it)));
            if (it == str.end())
                break;
        }
        for (auto it = str.begin(); it != str.end(); ++it)
            hashMapTail.insert(make_pair(string(it, str.end()), i + 1));
    }
    last = 0;
    for (auto i : hashMapHead)
    {
        if (last != i.first)
        {
            for (auto k : visit)
                ans = (ans + (((long long)last * (long long)k.first % MOD) * (long long)k.second) % MOD) % MOD;
            visit.clear();
        }
        auto range = hashMapTail.equal_range(i.second);
        for (auto j = range.first; j != range.second; ++j)
        {
            auto it = visit.find(j->second);
            if (it == visit.end())
                visit[j->second] = i.second.length();
            else if (i.second.length() > it->second)
                it->second = i.second.length();
        }
        last = i.first;
    }
    for (auto k : visit)
        ans = (ans + (((long long)last * (long long)k.first % MOD) * (long long)k.second) % MOD) % MOD;
    cout << ans << endl;
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}