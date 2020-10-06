/*
Environment: C11
Course: SUSTech_C++
Problem ID: Lab2_Excerise3
*/
#include <cstdio>
#include <cstdlib>
#include <cmath>
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    char a;
    int b;
    float c;
    printf("Please enter a character:\n");
    scanf("%c", &a);
    printf("Please enter an integer value:\n");
    scanf("%d", &b);
    printf("Please enter float value:\n");
    scanf("%f", &c);
    printf("The variables you entered were:\n");
    printf("The character value that you entered is: %c\n", a);
    printf("The integer value that you entered is: %d\n", b);
    printf("The float value that you entered is: %f\n", c);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}