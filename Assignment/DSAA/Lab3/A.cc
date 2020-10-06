/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab3_A
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define MAXN 200020
using namespace std;
int n, m;
int a[MAXN];
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
        scanf("%d%d", &n, &m);
        memset(a, 0, sizeof(a));
        for (int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        for (int i = n; i < n + m; ++i)
            scanf("%d", &a[i]);
        sort(a, a + n + m);
        for (int i = 0; i < n + m; ++i)
            printf("%d ", a[i]);
        printf("\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}