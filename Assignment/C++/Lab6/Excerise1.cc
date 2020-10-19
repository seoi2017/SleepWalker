/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab6_Excerise1
*/
#include <bits/stdc++.h>
using namespace std;
inline void displayMenu()
{
    printf("========================\n");
    printf("        M E N U         \n");
    printf("========================\n");
    printf("      1.  Add           \n");
    printf("      2.  Subtract      \n");
    printf("      3.  Multiply      \n");
    printf("      4.  Divide        \n");
    printf("      5.  Modulus       \n");
}
namespace thisFile
{
    inline int add(int &a, int &b)
    {
        return a + b;
    }
    inline int sub(int &a, int &b)
    {
        return a - b;
    }
    inline int mul(int &a, int &b)
    {
        return a * b;
    }
    inline int div(int &a, int &b)
    {
        return a / b;
    }
    inline int mod(int &a, int &b)
    {
        return a % b;
    }
}
int main()
{
    int ope, arg1, arg2, ans;
    char endAsk;
    displayMenu();
    do
    {
        printf("Enter your choice(1~5):");
        scanf("%d", &ope);
        printf("Enter your integer numbers:");
        scanf("%d%d", &arg1, &arg2);
        switch (ope)
        {
        case 1:
            ans = thisFile::add(arg1, arg2);
            break;
        case 2:
            ans = thisFile::sub(arg1, arg2);
            break;
        case 3:
            ans = thisFile::mul(arg1, arg2);
            break;
        case 4:
            ans = thisFile::div(arg1, arg2);
            break;
        case 5:
            ans = thisFile::mod(arg1, arg2);
            break;
        }
        printf("Result: %d\n", ans);
        printf("Press y or Y to continue:");
        scanf("\n%c", &endAsk);
    }
    while (endAsk == 'y' || endAsk == 'Y');
    return 0;
}