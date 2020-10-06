/*
Author: Invrise
OJ Site: Luogu
Problem ID: P5714
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int n;
    double m;
    cin >> n >> m;
    double bmi = n / (m * m);
    if (bmi < 18.5)
        cout << "Underweight" << endl;
    else if (bmi >= 18.5 && bmi < 24)
        cout << "Normal" << endl;
    else
        cout << bmi << endl
             << "Overweight" << endl;
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}