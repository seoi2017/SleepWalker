/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5709
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int m, s, t;
    scanf("%d%d%d", &m, &t, &s);
    printf("%d\n", t == 0 ? 0 : max(0, m - (int)((double)s / t + 0.999999)));
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}