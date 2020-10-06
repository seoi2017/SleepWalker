/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab3_C
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define MAXN 1020
using namespace std;
int n;
int a[MAXN], b[MAXN];
inline int insertion()
{
    int cnt = 0;
    for (int i = 1; i < n; ++i)
    {
        for (int j = i; j > 0; --j)
        {
            if (a[j - 1] > a[j])
            {
                cnt += 2;
                swap(a[j - 1], a[j]);
            }
        }
        ++cnt;
    }
    // printf("INS:%d\n", cnt);
    return cnt;
}
inline int selection()
{
    int cnt = 0;
    for (int i = 0, k; i < n - 1; ++i)
    {
        k = i;
        for (int  j = i + 1; j < n; ++j)
        {
            ++cnt;
            if (b[k] > b[j])
                k = j;
        }
        ++cnt;
        swap(b[i], b[k]);
    }
    // printf("SEL:%d\n", cnt);
    return cnt;
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &a[i]);
            b[i] = a[i];
        }
        if (insertion() < selection())
        {
            for (int i = 0; i < n; ++i)
                printf("%d ", a[i]);
            printf("\nInsertion Sort wins!\n");
        }
        else
        {
            for (int i = 0; i < n; ++i)
                printf("%d ", b[i]);
            printf("\nSelection Sort wins!\n");
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}