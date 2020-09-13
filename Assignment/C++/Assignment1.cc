/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Assignment_1
*/
#include <bits/stdc++.h>
#define MAX_SUM 16384
using namespace std;
typedef long long ll_t;
class ubigint_t
{
private:
    const int base = 1e8;
    const int power = 8;
    ll_t s[MAX_SUM];

    inline bool checkValue(const char &chr)
    {
        if (chr >= '0' && chr <= '9')
            return true;
        else
            return false;
    }

public:
    ubigint_t()
    {
        memset(this->s, 0, sizeof(this->s));
    }

    ubigint_t(const char *str)
    {
        *this = str;
    }

    bool operator=(const char *str)
    {
        memset(this->s, 0, sizeof(this->s));
        int len = strlen(str);
        this->s[0] = (len + power - 1) / power;
        for (int i = 0, t = 0, w; i < len; w *= 10, ++i)
        {
            if (i % power == 0)
                w = 1, ++t;
            if (this->checkValue(str[i]) == false)
                return false;
            this->s[t] += (w * (str[i] - '0'));
        }
        return true;
    }

    ubigint_t operator*(const ubigint_t &x) const
    {
        ubigint_t z;
        z.s[0] = x.s[0] + this->s[0] - 1;
        for (int i = 1; i <= x.s[0]; ++i)
            for (int j = 1; j <= this->s[0]; ++j)
            {
                z.s[i + j - 1] += (x.s[i] * this->s[j]);
                z.s[i + j] += z.s[i + j - 1] / base;
                z.s[i + j - 1] %= base;
            }
        while (z.s[z.s[0] + 1])
            ++z.s[0];
        while (!z.s[z.s[0]] && z.s[0] > 1) //为了应对乘0
            --z.s[0];
        return z;
    }

    void print()
    {
        printf("%lld", this->s[this->s[0]]);
		for (int i = this->s[0] - 1; i > 0; --i)
			printf("%0*lld", power, this->s[i]);
        printf("\n");
    }
};

int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    char a[MAX_SUM * 8], b[MAX_SUM * 8];
    bool minusA = false, minusB = false;
    ubigint_t x, y;
    printf("Please input two integers\n");
    scanf("\n%s%s", a, b);
    if (a[0] == '-')
        minusA = true;
    if (b[0] == '-')
        minusB = true;
    int tA = (minusA ? 1 : 0), tB = (minusB ? 1 : 0);
    reverse(a + tA, a + strlen(a));
    reverse(b + tB, b + strlen(b));
    if (!(x = (a + tA)) || !(y = (b + tB)))
        printf("Invalid input!\n");
    else
    {
        ubigint_t ans = x * y;
        if (minusA ^ minusB)
            printf("-");
        ans.print();
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}