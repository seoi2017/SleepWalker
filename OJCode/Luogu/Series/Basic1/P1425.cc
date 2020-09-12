/*
Author: Invrise
OJ Site: Luogu
Problem ID: P1425
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    int ans = (c * 60 + d) - (a * 60 + b);
    printf("%d %d\n", ans / 60, ans % 60);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}