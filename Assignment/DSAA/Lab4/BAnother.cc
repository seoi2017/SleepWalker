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
#include <list>
#define MAXN 100010
using namespace std;
int len;
char str[MAXN];
bool change;
list<char> ans;
list<char>::iterator nowPos;
inline void print()
{
    for (list<char>::iterator it = ans.begin(); it != ans.end(); ++it)
        printf("%c", *it);
    printf("\n");
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d\n%s", &len, str);
        ans.clear();
        nowPos = ans.begin();
        change = false;
        for (int i = 0; i < len; ++i)
        {
            switch (str[i])
            {
            case 'r':
                change = true;
                continue;
            case 'I':
                nowPos = ans.begin();
                continue;
            case 'H':
                if (nowPos != ans.begin())
                    --nowPos;
                continue;
            case 'L':
                if (nowPos != ans.end())
                    ++nowPos;
                continue;
            case 'x':
                if (nowPos != ans.end())
                    nowPos = ans.erase(nowPos);
                continue;
            default:
                if (change == true && nowPos != ans.end())
                    *nowPos = str[i];
                else
                {
                    nowPos = ans.insert(nowPos, str[i]);
                    if (change == false)
                        ++nowPos;
                }
                change = false;
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