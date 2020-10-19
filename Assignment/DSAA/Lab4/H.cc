/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_H
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <list>
using namespace std;
int n, m;
char ope;
list<int> lst;
list<int>::iterator it;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 0, temp; i < n; ++i)
    {
        scanf("%d", &temp);
        lst.push_back(temp);
    }
    for (int i = 0, j, arg1, arg2; i < m; ++i)
    {
        scanf("\n%c%d", &ope, &arg1);
        switch (ope)
        {
        case 'i':
            scanf("%d", &arg2);
            it = lst.begin();
            for (j = 0; j < arg1 - 1; ++j)
                ++it;
            lst.insert(it, arg2);
            break;
        case 'q':
            it = lst.begin();
            for (j = 0; j < arg1 - 1; ++j)
                ++it;
            printf("%d\n", *it);
            break;
        case 'r':
            it = lst.begin();
            for (j = 0; j < arg1 - 1; ++j)
                ++it;
            lst.erase(it);
            break;
        default:
            break;
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}