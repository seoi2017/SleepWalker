/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5713
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
    printf("%s", 5 * n < 11 + 3 * n ? "Local" : "Luogu");
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}