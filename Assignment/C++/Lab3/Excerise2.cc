/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab3_Excerise2
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int sum = 0;
    string str;
    cout << "Enter words(to stop, type the word done)" << endl;
    do
    {
        cin >> str;
        ++sum;
    }
    while (str != "done");
    cout << "You entered a total of " << (--sum) << " words." << endl;
    return 0;
}