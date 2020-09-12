/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5710
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    bool a, b;
    a = n % 2 == 0 ? true : false;
    b = n > 4 && n < 13 ? true : false;
    printf("%d ", a && b ? 1 : 0);
    printf("%d ", a || b ? 1 : 0);
    printf("%d ", (a && !b) || (b && !a) ? 1 : 0);
    printf("%d\n", !a && !b ? 1 : 0);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}