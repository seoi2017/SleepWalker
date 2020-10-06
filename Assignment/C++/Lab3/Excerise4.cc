/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab3_Excerise4
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a, b, c;
    double avg;
    char level;
    cout << "Enter the quiz, mid-term and fina scores:";
    cin >> a >> b >> c;
    avg = ((double)a + b + c) / 3;
    if (avg >= 90)
        level = 'A';
    else if (avg >= 70 && avg < 90)
        level = 'B';
    else if (avg >= 50 && avg < 70)
        level = 'C';
    else
        level = 'F';
    printf("average score = %.4f, grade = %c\n", avg, level);
    return 0;
}