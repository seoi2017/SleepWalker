/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_D
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <set>
#include <cstdlib>
using namespace std;
multiset<int> mp;
multiset<int>::iterator l, r;
int n;
inline void update(int x)
{
    int sizeOld = mp.size();
    mp.insert(x);
    int sizeNew = sizeOld + 1;
    if (sizeNew == 1)
        l = r = mp.begin();
    else if(sizeOld & 1)
    {
        if (x < (*l))
            --l;
        else if (x > (*r))
            ++r;
    }
    else
    {
        if (x > (*l) && x < (*r))
            --r, ++l;
        else if (x <= (*l))
            l = --r;
        else
            ++l;
    }
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
        mp.clear();
        for (int i = 0, temp; i < n; ++i)
        {
            scanf("%d", &temp);
            update(temp);
            if (i % 2 != 0)
                continue;
            printf("%d ", (*l + *r) / 2);
        }
        printf("\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}