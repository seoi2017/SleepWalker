/*
Author: Invrise
OJ Site: Luogu
Problem ID: P1421
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int a, b;
    scanf("%d%d", &a, &b);
    int money = a * 10 + b;
    printf("%d", money / 19);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}