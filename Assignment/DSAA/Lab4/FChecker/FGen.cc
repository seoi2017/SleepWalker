// Data Generator of Problem F
#include <bits/stdc++.h>
using namespace std;
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
    int T = 10;
    printf("%d\n", T);
    while (T--)
    {
        int n = random(100000) + 100000, m = random(10000);
        for (int i = 0; i < n; ++i)
            printf("%c", randChar());
        printf("\n%d\n", m);
        for (int i = 0, temp; i < m; ++i)
        {
            temp = random(2);
            if (temp == 1)
                printf("1 %c %d\n", randChar(), random(n++));
            else
                printf("2 %d\n", random(n));
        }
            
    }
    fclose(stdout);
    return 0;
}