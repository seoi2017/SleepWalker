/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Lab2_Excerise1
*/
#include <bits/stdc++.h>
using namespace std;
char *oper[] = {"x=y+3", "x=y-2", "x=y*5", "x=x/y", "x=x%y"};
int func(int index, int x, int y)
{
    switch(index)
    {
    case 0:
        return y + 3;
    case 1:
        return y - 2;
    case 2:
        return y * 5;
    case 3:
        return x / y;
    case 4:
        return x % y;
    default:
        break;
    }
}
void printC(int x, int y)
{
    printf("x value\ty value\tExpressions\tResult\t\n");
    for (int i = 0; i < 5; ++i)
    {
        printf("\t%d\t|\t%d\t|\t%s\t|\tx=%d\t\n", x, y, oper[i], func(i, x, y));
    }
}
void printCPP(int x, int y)
{
    cout.setf(ios_base::skipws);
    cout << "x value" << setw(8) << "y value" << setw(8) << "Expressions" << setw(8) << "Result" << endl;
    for (int i = 0; i < 5; ++i)
    {
        cout << setw(4) << x << setw(4) << "|" << setw(4) << y << setw(4) << "|" << setw(8) << oper[i] << setw(4) << "|" << setw(4) << "x=" << func(i, x, y) << endl;
    }
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int a, b;
    scanf("%d%d", &a, &b);
    printC(a, b);
    printCPP(a, b);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}