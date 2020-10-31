/*
Author: Invrise
OJ Site: Luogu
Problem ID: P4414
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int *a = new int[3];
    char *str = new char[4];
    for (int i = 0; i < 3; ++i)
        scanf("%d", a + i);
    sort(a, a + 3);
    scanf("%s", str);
    for (int i = 0; i < 3; ++i)
        switch (str[i])
        {
        case 'A':
            printf("%d ", a[0]);
            break;
        case 'B':
            printf("%d ", a[1]);
            break;
        case 'C':
            printf("%d ", a[2]);
            break;
        default:
            break;
        }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}