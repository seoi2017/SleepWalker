/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab3_Excerise1
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, sum = 0;
    do
    {
        cout << "Enter an integer number: ";
        cin >> n;
        cout << "The cumulative sum of the entires to date is: " << (sum += n) << endl;
    }
    while (n != 0);
    return 0;
}