/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5712
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
    printf("Today, I ate %d apple%s", n, n > 1 ? "s." : ".");
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}