/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5705
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    char str[8];
    scanf("%s", str);
    for (int i = 0; i < strlen(str) / 2; ++i)
    {
        swap(str[i], str[strlen(str) - i - 1]);
    }
    printf("%s\n", str);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}