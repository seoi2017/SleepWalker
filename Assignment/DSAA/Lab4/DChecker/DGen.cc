// Data Generator of Problem D
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 300000;
inline int random(int maxn)
{
    return rand() % maxn + 1;
}
inline int randChar()
{
    return rand() % 26 + 'a';
}
int main()
{
    freopen("in.io", "w", stdout);
    srand(time(0));
    int T = 10;
    printf("%d\n", T);
    while (T--)
    {
        int n = random(MAXN);
        printf("%d\n", n);
        for (int i = 0; i < n; ++i)
            printf("%d ", random(MAXN));
        printf("\n");   
    }
    fclose(stdout);
    return 0;
}