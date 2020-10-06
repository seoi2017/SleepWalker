/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5715
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int a[] = {0, 0, 0};
    for (int &i : a)
        cin >> i;
    sort(a, a + 3);
    for (int &i : a)
        cout << i << (&i == a + 2 ? "\n" : " ");
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}