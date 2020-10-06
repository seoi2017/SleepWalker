/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab2_Excerise2
*/
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull_t;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    ull_t n;
    printf("Enter the number of seconds:\n");
    scanf("%llu", &n);
    printf("%llu seconds = %llu days, %llu hours, %llu minutes, %llu seconds", n, n / 86400 , n % 86400 / 3600, n % 86400 % 3600 / 60, n % 86400 % 3600 % 60);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}