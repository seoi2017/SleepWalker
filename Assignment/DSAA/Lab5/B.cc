/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab5_B
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 20000010
using namespace std;
class Queue
{
private:
    int head, tail;
    int array[MAXN];
public:
    Queue(): head(0), tail(0) {}
    void enQueue(const int &x)
    {
        this->array[this->tail++] = x;
    }
    bool isEmpty()
    {
        if (this->head == this->tail)
            return true;
        return false;
    }
    int deQueue()
    {
        if (this->isEmpty() == true)
            return INT32_MIN;
        else
            return this->array[this->head++];
    }
    int getHead()
    {
        if (this->isEmpty() == true)
            return INT32_MIN;
        else
            return this->array[this->head];
    }
}queue;
int val;
char ope;
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
        scanf("\n%c", &ope);
        switch (ope)
        {
        case 'E':
            scanf("%d", &val);
            queue.enQueue(val);
            break;
        case 'D':
            queue.deQueue();
            break;
        case 'A':
            printf("%d\n", queue.getHead());
            break;
        default:
            break;
        }
    }
    while (queue.isEmpty() == false)
        printf("%d ", queue.deQueue());
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}