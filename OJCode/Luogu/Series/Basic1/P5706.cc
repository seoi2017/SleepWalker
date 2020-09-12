/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5706
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    double a;
    int b;
    scanf("%lf%d", &a, &b);
    printf("%.3lf\n%d\n", a / b, b * 2);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}