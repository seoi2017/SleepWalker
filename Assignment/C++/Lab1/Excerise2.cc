/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab1_Excerise2
*/
#include <bits/stdc++.h>
using namespace std;
inline void smile()
{
    cout << "Smile!";
}
inline void print()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3 - i; ++j)
        {
            smile();
        }
        cout << endl;
    }
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    print();
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}