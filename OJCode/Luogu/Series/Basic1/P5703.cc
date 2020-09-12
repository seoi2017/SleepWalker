/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5703
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    long long a, b;
    scanf("%lld%lld", &a, &b);
    printf("%lld", a * b);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}