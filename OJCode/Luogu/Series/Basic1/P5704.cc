/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5704
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    char c;
    scanf("%c", &c);
    printf("%c\n", c + ('A' - 'a'));
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}