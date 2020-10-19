/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_F
*/
#pragma GCC optimize (3)
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
using namespace std;
string str, arg1;
int n, ope, arg2;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--)
    {
        cin >> str;
        cin >> n;
        while (n--)
        {
            cin >> ope;
            if (ope == 1)
            {
                cin >> arg1 >> arg2;
                str.insert(arg2 - 1, arg1);
            }
            else
            {
                cin >> arg2;
                cout << str[arg2 - 1] << endl;
            }
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}