/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5711
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
    if (n % 100 == 0 && n % 400 == 0)
        printf("1");
    else if (n % 100 != 0 && n % 4 == 0)
        printf("1");
    else
        printf("0");
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}