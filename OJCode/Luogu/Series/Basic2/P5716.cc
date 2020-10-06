/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5716
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year, month;
    cin >> year >> month;
    if (month != 2)
        cout << days[month];
    else
        cout << days[2] + ((year % 100 == 0 && year % 400 == 0) || (year % 100 != 0 && year % 4 == 0) ? 1 : 0);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}