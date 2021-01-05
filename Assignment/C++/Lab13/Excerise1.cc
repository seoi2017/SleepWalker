/*
Environment: C++17
Course: SUSTech_C++
Problem ID: Lab13_Excerise1
*/
#include <bits/stdc++.h>
using namespace std;
template<class T>
T getMax(const T& x, const T& y)
{
    return x > y ? x : y;
}
int main()
{
    int a = 1, b = 2;
    double c = 3.0, d = 1.2;
    string e = "hello", f = "world";
    cout << getMax(a, b) << endl;
    cout << getMax(c, d) << endl;
    cout << getMax(e, f) << endl;
    return 0;
}