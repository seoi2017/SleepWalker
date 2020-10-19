/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab5_Excerise3
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int *array = new int[5];
    cout << "Enter 5 integers:" << endl;
    for (auto i = array; i < array + 5; ++i)
        cin >> *i;
    cout << "The elements of the array in reserve order are:" << endl;
    for (auto i = array + 4; i >= array; --i)
        cout << *i << " ";
    cout << endl;
    delete[] array;
    return 0;
}