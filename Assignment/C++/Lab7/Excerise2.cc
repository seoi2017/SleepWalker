/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab7_Excerise2
*/
#include <bits/stdc++.h>
using namespace std;
template<typename T, size_t N>
auto getMax(const T (&arg)[N])
{
    T *value = new T();
    for (int i = 0; i < N; ++i)
        *value = max(*value, arg[i]);
    return *value;
}
int main()
{
    int intArray[5] = {0};
    for (int i = 0; i < 5; ++i)
        cin >> intArray[i];
    cout << "Max int: " << getMax(intArray) << endl;
    double doubleArray[5] = {0};
    for (int i = 0; i < 5; ++i)
        cin >> doubleArray[i];
    cout << "Max double: " << getMax(doubleArray) << endl;
    
    return 0;
}