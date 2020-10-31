/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab5_D
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 200010
using namespace std;
class Stack
{
public:
    struct Node
    {
        int index, value;
        Node(int x = 0, int y = 0): value(x), index(y) {}
    };
private:
    Node array[MAXN];
    int cnt;
public:
    Stack(): cnt(0) {}
    Node top()
    {
        if (this->isEmpty() == false)
            return this->array[this->cnt - 1];
        return Node(-1, -1);
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
    void push(int val, int ind)
    {
        this->array[this->cnt++] = Node(val, ind);
    }
    void clear()
    {
        this->cnt = 0;
    }
}stack;
int n, m, ans[MAXN];
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
        scanf("%d", &n);
        stack.clear();
        memset(ans, -1, sizeof(ans));
        for (int i = 0, temp; i < n; ++i)
        {
            scanf("%d", &temp);
            while (stack.isEmpty() == false && stack.top().value < temp)
            {
                ans[stack.top().index] = i - stack.top().index;
                stack.pop();
            }
            stack.push(temp, i);
        }
        scanf("%d", &m);
        for (int i = 0, temp; i < m; ++i)
        {
            scanf("%d", &temp);
            printf("%d\n", ans[temp - 1]);
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}