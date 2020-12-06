#include <bits/stdc++.h>
#include "matrix.hpp"

using namespace std;

inline void demo1()
{
    cout << "==== Testing Demo 1 ====" << endl;
    Matrix a, b(5), c(3, 4);
    float data[] = {1, 2, 3, 4, 5, 6};
    Matrix d = Matrix::getInstance(data, 3, 2);
    Matrix e(d);
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;
    cout << e << endl;
    e(1, 1) += 100;
    cout << d << endl;
    cout << e << endl;
}

inline void demo2()
{
    cout << "==== Testing Demo 2 ====" << endl;
    Matrix a(2, 3), b (3, 2);
    a += 2, b += 3;
    cout << a << endl;
    cout << b << endl;
    Matrix c = a * b;
    cout << c << endl;
    Matrix d(2);
    d(0, 0) += 1, d(1, 1) += 2;
    Matrix e = c + d, f = c - d;
    cout << e << endl;
    cout << f << endl;
    Matrix g = c;
    g(1, 1) = 100;
    cout << c << endl;
}

inline void demo3()
{
    cout << "==== Testing Demo 3 ====" << endl;
    Matrix a(2, 3), b (3, 2);
    a += 2, b += 3;
    Matrix c = a, d = a.clone();
    d += 1;
    cout << a << endl;
    cout << d << endl;
    cout << (a == c) << " " << (a == d) << endl;
    cout << a[1][1] << " " << b(1, 1) << endl;
    cout << endl << a.transpose() << endl;
    Matrix e = b.subMatrix(1, 1, 2, 1);
    cout << e << endl;
}

int main()
{
    try
    {
        demo1();
        // demo2();
        // demo3();
    }
    catch(const MatrixException& e)
    {
        cerr << e.what() << endl;
    }
    return 0;
}