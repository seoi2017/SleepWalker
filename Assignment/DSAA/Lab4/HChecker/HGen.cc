// Data Generator of Problem H
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1000;
constexpr int MAXM = 1000000000;
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
        printf("%d ", random(MAXM));
    printf("\n");
    for (int i = 0, ope; i < m; ++i)
    {
        ope = random(3);
        switch (ope)
        {
        case 1:
            printf("i %d %d\n", random(n++), random(MAXM));
            break;
        case 2:
            printf("r %d\n", random(n--));
            break;
        case 3:
            printf("q %d\n", random(n));
            break;
        default:
            break;
        }
    }
    fclose(stdout);
    return 0;
}