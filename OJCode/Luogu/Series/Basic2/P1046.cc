/*
Author: Invrise
OJ Site: Luogu
Problem ID: P1046
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int a[10] = {0}, top, ans;
    for (int i = 0; i < 10; ++i)
        scanf("%d", &a[i]);
    scanf("%d", &top);
    top += 30;
    for (int i = 0; i < 10; ++i)
        if (top >= a[i])
            ++ans;
    printf("%d", ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}