/*
Environment: C++17
Course: SUSTech_C++
Problem ID: Lab10_Excerise1&2
*/
#include "Complex.h"
#include "Number.h"
#include <bits/stdc++.h>

using namespace std;

inline void excerise1()
{
    Complex a(3.0, 4.0);
    Complex b(2.0, 6.0);
    cout << "b is " << b << endl;
    cout << "~b is " << ~b << endl;
    cout << "a is " << a << endl;
    cout << "a + b is " << a + b << endl;
    cout << "a - b is " << a - b << endl;
    cout << "a * b is " << a * b << endl;
    cout << "a / b is " << a / b << endl;
    cout << "2 * b is " << 2 * b << endl;
    cout << "b * 2 is " << b * 2 << endl;
    cout << "2 + a is " << 2 + a << endl;
    cout << "a + 2 is " << a + 2 << endl;
    Complex c = b;
    cout << "b == c is " << (b == c) << endl;
    cout << "b != c is " << (b != c) << endl;
    cout << "a == c is " << (a == c) << endl;
    Complex d;
    cin >> d;
    cout << "d is " << d << endl;
}

inline void excerise2()
{
    Number n1(20);
    Number n2 = n1++;
    cout << n1 << " " << n2 << endl;
    Number n3 = n2--;
    cout << n2 << " " << n3 << endl;
    Number n4 = ++n3;
    cout << n3 << " " << n4 << endl;
    Number n5 = --n4;
    cout << n4 << " " << n5 << endl;
}

int main()
{
    int type;
    tag:
    cout << "Input Excerise Number of Lab10: ";
    switch(cin >> type; type)
    {
    case 1:
        excerise1();
        break;
    case 2:
        excerise2();
        break;
    default:
        cout << "Unknown Input, Please Retry." << endl;
        goto tag;
        break;
    }
    return 0;
}