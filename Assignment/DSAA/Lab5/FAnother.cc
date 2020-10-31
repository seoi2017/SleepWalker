/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab5_F
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <deque>
#define MAXN 3000010
using namespace std;
int n, k, ans, val[MAXN];
deque<int> inc, des;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d%d", &k, &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &val[i]);
    ans = 0;
    for (int l = 0, r = 0; r < n; ++r)
    {
        while (inc.empty() == false && val[inc.back()] > val[r])
            inc.pop_back();
        inc.push_back(r);
        while (des.empty() == false && val[des.back()] < val[r])
            des.pop_back();
        des.push_back(r);
        while (val[des.front()] - val[inc.front()] > k)
        {
            while (inc.empty() == false && inc.front() <= l)
                inc.pop_front();
            while (des.empty() == false && des.front() <= l)
                des.pop_front();
            ++l;
        }
        ans = max(ans, r - l + 1);
    }
    printf("%d\n", ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}