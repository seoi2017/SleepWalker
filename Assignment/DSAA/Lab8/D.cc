/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab8_D
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXK 1010
using namespace std;
using BigInt = long long;
BigInt t, k, lastAns, heap[MAXK], top = 0LL;
inline void insert(const BigInt& x)
{
    heap[++top] = x;
    BigInt now = top, nxt;
    while (now > 1)
    {
        nxt = now >> 1;
        if (heap[now] >= heap[nxt])
            return;
        swap(heap[now], heap[nxt]);
        now = nxt;
    }
}
inline void remove()
{
    swap(heap[1], heap[top--]);
    BigInt now = 1, nxt;
    while ((now << 1) <= top)
    {
        nxt = now << 1;
        if (nxt < top && heap[nxt + 1] < heap[nxt])
            ++nxt;
        if (heap[now] <= heap[nxt])
            return;
        swap(heap[now], heap[nxt]);
        now = nxt;
    }
}
inline BigInt funcA(const BigInt& x)
{
    BigInt result = x, temp = x;
    while (temp != 0)
        result += temp % 10, temp /= 10;
    return result;
}
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    cin >> t >> k >> lastAns;
    for (BigInt i = 1, temp; i <= t; ++i)
    {
        temp = funcA(i + lastAns);
        if (top < k)
            insert(temp);
        else if (heap[1] < temp)
        {
            remove();
            insert(temp);
        }
        if (i % 100 == 0)
        {
            lastAns = heap[1];
            cout << lastAns << " ";
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}