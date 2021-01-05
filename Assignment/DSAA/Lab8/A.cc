/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab8_A
*/
#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <queue>
#define MAXN 100010
using namespace std;
vector<int> node[MAXN];
int n, value[MAXN], onlyRoot;
bool notRoot[MAXN], failFlag;
bool judge(const int& root, bool isLess)
{
    queue<int> qfa, qson;
    qfa.push(root);
    int mount = 2, lastSon = 0;
    tagLoop:
    while (qfa.empty() == false)
    {
        int fa = qfa.front(), cntSon = 0;
        qfa.pop();
        for (int son : node[fa])
        {
            if (isLess ? value[son] < value[fa] : value[son] > value[fa])
                return false;
            qson.push(son);
            ++cntSon;
        }
        for (int i = cntSon; i < 2; ++i)
            qson.push(-1);
    }
    if (qson.size() > mount)
        return false;
    lastSon = 0;
    while (qson.empty() == false)
    {
        int nowSon = qson.front();
        qson.pop();
        if (nowSon != -1 && lastSon == -1)
            return false;
        if (nowSon != -1)
            qfa.push(nowSon);
        lastSon = nowSon;
    }
    mount *= 2;
    if (qfa.empty() == false)
        goto tagLoop;
    return true;
}
inline bool isHeap()
{
    bool isLessHeap = judge(onlyRoot, true);
    bool isGreaterHeap = judge(onlyRoot, false);
    return isLessHeap || isGreaterHeap;
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    cin >> T;
    for (int k = 1; k <= T; ++k)
    {
        cin >> n;
        failFlag = true;
        memset(notRoot, false, sizeof(notRoot));
        for (int i = 1; i <= n; ++i)
        {
            node[i].clear();
            cin >> value[i];
        }
        for (int i = 1, st, ed; i < n; ++i)
        {
            cin >> st >> ed;
            node[st].push_back(ed);
            notRoot[ed] = true;
        }
        onlyRoot = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (notRoot[i] == false)
                if (onlyRoot == 0)
                    onlyRoot = i;
                else
                {
                    failFlag = false;
                    break;
                }
        }
        cout << "Case #" << k << ": " << (failFlag && isHeap() == true ? "YES" : "NO") << endl;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}