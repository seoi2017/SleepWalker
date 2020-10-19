#include <bits/stdc++.h>
using namespace std;
inline int random(int x)
{
    return rand() % x + 1;
}
inline char randomOper(bool end)
{
    char ope[] = {'#', 'r', 'I', 'H', 'L', 'x'};
    if (end == true)
        return ope[random(4) + 1];
    else
        return ope[random(5)];
}
int main()
{
    freopen("in.io", "w", stdout);
    srand(time(0));
    int n = random(20);
    cout << n << endl;
    for (int i = 0; i < n; ++i)
    {
        int len = 100000;
        cout << len << endl;
        for (int j = 0; j < len; ++j)
        {
            if (random(2) == 1)
                cout << random(9);
            else
            {
                char oper = randomOper(j == len - 1);
                cout << oper;
                if (oper == 'r')
                {
                    cout << random(9);
                    ++j;
                }
            }
        }
        cout << endl;
    }
    fclose(stdout);
    return 0;
}