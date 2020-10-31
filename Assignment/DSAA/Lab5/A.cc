/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab5_A
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 30010
using namespace std;
class Stack
{
private:
    int cnt;
    char array[MAXN];
public:
    Stack(): cnt(0) {}
    char top()
    {
        if (this->isEmpty() == false)
            return this->array[this->cnt - 1];
        return 0;
    }
    bool isEmpty()
    {
        return this->cnt == 0 ? true : false;
    }
    bool pop()
    {
        if (this->isEmpty() == true)
            return false;
        --this->cnt;
        return true;
    }
    void push(const char &chr)
    {
        this->array[this->cnt++] = chr;
    }
    void clear()
    {
        this->cnt = 0;
    }
}stack;
int n;
char temp;
bool falseFlag;
inline char otherSide(const char &chr)
{
    switch (chr)
    {
        case ')':
            return '(';
        case ']':
            return '[';
        case '}':
            return '{';
        default:
            return 0;
    }
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d\n", &n);
        falseFlag = false;
        stack.clear();
        for (int i = 0; i < n; ++i)
        {
            scanf("%c", &temp);
            if (falseFlag == true)
                continue;
            switch (temp)
            {
            case '(':
            case '[':
            case '{':
                stack.push(temp);
                break;
            case ')':
            case ']':
            case '}':
                if (stack.isEmpty() == true || stack.top() != otherSide(temp))
                    falseFlag = true;
                else
                    stack.pop();
                break;
            default:
                break;
            }
        }
        if (falseFlag == true || stack.isEmpty() == false)
            printf("NO\n");
        else
            printf("YES\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}