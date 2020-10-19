/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_B
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 100010
using namespace std;
struct Node
{
    char chr;
    int pre, nxt;
}pool[MAXN];
bool orderR;
int n, nowPos, tot;
char c;
inline void print()
{
    for (int it = pool[0].nxt; pool[it].nxt != -1; it = pool[it].nxt)
        cout << pool[it].chr;
    cout << endl;
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n;
        nowPos = tot = 1;
        orderR = false;
        pool[0].pre = pool[1].nxt = -1;
        pool[1].pre = 0, pool[0].nxt = 1;
        pool[0].chr = pool[1].chr = -1;
        for (int i = 0; i < n; ++i)
        {
            cin >> c;
            switch (c)
            {
            case 'r':
                orderR = true;
                continue;
            case 'I':
                nowPos = pool[0].nxt;
                continue;
            case 'H':
                if (pool[nowPos].pre != 0)
                    nowPos = pool[nowPos].pre;
                continue;
            case 'L':
                if (pool[nowPos].nxt != -1)
                    nowPos = pool[nowPos].nxt;
                continue;
            case 'x':
                if (pool[nowPos].nxt != -1)
                {
                    pool[pool[nowPos].pre].nxt = pool[nowPos].nxt;
                    pool[pool[nowPos].nxt].pre = pool[nowPos].pre;
                    nowPos = pool[nowPos].nxt;
                }
                continue;
            default:
                if (!isdigit(c))
                    continue;
                if (orderR == true && pool[nowPos].chr != -1)
                    pool[nowPos].chr = c;
                else
                {
                    pool[++tot].chr = c;
                    pool[tot].nxt = nowPos;
                    pool[tot].pre = pool[nowPos].pre;
                    pool[pool[nowPos].pre].nxt = tot;
                    pool[nowPos].pre = tot;
                    if (orderR == true)
                        nowPos = pool[nowPos].pre;
                }
                orderR = false;
                break;
            }
        }
        print();
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}