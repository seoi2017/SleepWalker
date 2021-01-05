/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab6_D
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 200010
using namespace std;
char str[MAXN];
int len, fail[MAXN];
inline void solve()
{
    fail[0] = 0;
    fail[1] = 0;
    for (int i = 1, k; i < len; ++i)
    {
        k = fail[i];
        while (k != 0 && str[i] != str[k])
            k = fail[k];
        fail[i + 1] = (str[i] == str[k] ? k + 1 : 0);
    }
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
        scanf("%s", str);
        len = strlen(str);
        solve();
        if (fail[len] == 0)
            printf("%d\n", len);
        else if (len % (len - fail[len]) == 0)
            printf("0\n");
        else
            printf("%d\n", len - fail[len] - (len % (len - fail[len])));        
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}