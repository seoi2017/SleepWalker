/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab3_B
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define MAXN 5000020
using namespace std;
int n, m;
int a[MAXN];
int findKth(int l, int r, int k)
{
    if (l < r)
    {
        int i = l;
        for (int j = l; j < r; ++j)
        {
            if (a[j] < a[r])
                swap(a[i++], a[j]);
        }
        swap(a[i], a[r]);
        if (k == i)
            return a[i];
        else if (k < i)
            return findKth(l, i - 1, k);
        else
            return findKth(i + 1, r, k);
    }
    else return a[l];
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    printf("%d", findKth(0, n - 1, m - 1));
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}