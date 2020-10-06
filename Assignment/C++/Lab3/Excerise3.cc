/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab3_Excerise3
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n = 7;
    for (int i = 1; i <= 7; ++i)
    {
        for (int j = 1; j <= 7; ++j)
            if (j <= i)
                printf("%d", j);
            else
                printf("*");
        printf("\n");
    }
    return 0;
}