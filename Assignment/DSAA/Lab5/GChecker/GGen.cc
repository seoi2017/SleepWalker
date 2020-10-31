// Data Generator of Problem G
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 300000;
constexpr int MAXM = 300000;
constexpr int MAXVAL = 1000000000;
inline int random(int maxn)
{
    return rand() % maxn + 1;
}
int main()
{
    freopen("in.io", "w", stdout);
    srand(time(0));
    int n = random(MAXN), m = random(MAXN);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; ++i)
        printf("%d ", random(MAXVAL));
    printf("\n");
    for (int i = 0, l, r; i < m; ++i)
    {
        l = random(n), r = random(n);
        if (l > r)
            swap(l, r);
        printf("%d %d\n", l, r);
    }
    fclose(stdout);
    return 0;
}