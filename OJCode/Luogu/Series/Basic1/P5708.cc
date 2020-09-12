/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5708
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    double a, b, c;
    scanf("%lf%lf%lf", &a, &b, &c);
    double p = 1.0 / 2.0 * (a + b + c);
    printf("%.1lf", sqrt(p * (p - a) * (p - b) * (p - c)));
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}