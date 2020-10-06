/*
Author: Invrise
OJ Site: Luogu
Problem ID: P1055
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    string str;
    int ans = 0;
    char index[] = "0123456789X";
    cin >> str;
    for (int i = 0, j = 1; i < str.length() - 1; ++i)
        if (str[i] == '-')
            continue;
        else
            ans += j++ * (str[i] == 'X' ? 10 : str[i] - '0');
    if (index[ans % 11] == str[str.length() - 1])
        cout << "Right";
    else
        cout << str.substr(0, str.length() - 1) << index[ans % 11];
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}