/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5717
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
    for (int i = 0; i < 3; ++i)
        scanf("%d", a + i);
    sort(a, a + 3);
    if (a[0] + a[1] <= a[2])
        printf("Not triangle\n");
    else
    {
        if (a[0] * a[0] + a[1] * a[1] == a[2] * a[2])
            printf("Right triangle\n");
        else if (a[0] * a[0] + a[1] * a[1] > a[2] * a[2])
            printf("Acute triangle\n");
        else
            printf("Obtuse triangle");
        if (a[0] == a[1])
            printf("Isosceles triangle\n");
        if (a[0] == a[1] && a[1] == a[2])
            printf("Equilateral triangle\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}