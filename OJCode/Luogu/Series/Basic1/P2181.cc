/*
Author: Invrise
OJ Site: Luogu
Problem ID: P2181
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    unsigned long long n;
    scanf("%lld", &n);
    printf("%lld", n * (n - 1) / 2 * (n - 2) / 3 * (n - 3) / 4); // 拆分除法+无符号长整数型防爆炸
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}