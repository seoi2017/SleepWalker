/*
Author: Invrise
OJ Site: Luogu
Problem ID: P2433
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    double pi__ = 3.141593;
    scanf("%d", &T);
    switch (T)
    {
    case 1:
        printf("I love Luogu!");
        break;
    case 2:
        printf("6 4");
        break;
    case 3:
        printf("3\n12\n2");
        break;
    case 4:
        printf("166.667");
        break;
    case 5:
        printf("15");
        break;
    case 6:
        cout << sqrt(36 + 81);
        break;
    case 7:
        printf("110\n90\n0");
        break;
    case 8:
        cout << 2 * pi__ * 5 << endl
             << pi__ * 25 << endl
             << 4.0 / 3.0 * pi__ * 125;
        break;
    case 9:
        printf("22");
        break;
    case 10:
        printf("9\n");
        break;
    case 11:
        cout << 100.0 / 3.0 << endl;
        break;
    case 12:
        printf("%d\n", 'M' - 'A' + 1);
        printf("%c", 'A' + 17);
        break;
    case 13:
        printf("%.0f\n", pow((4.0 / 3.0 * pi__ * 64) + (4.0 / 3.0 * pi__ * 1000), 1.0 / 3.0));
        break;
    case 14:
        printf("50\n");
        break;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}