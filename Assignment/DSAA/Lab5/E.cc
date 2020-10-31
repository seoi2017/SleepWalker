/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab5_E
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 100010
using namespace std;
class Stack
{
private:
    struct Node
    {
        int value;
        Node *next;
        Node(const int &x, Node *y): value(x), next(y) {}
    }*head;
public:
    Stack(): head(nullptr) {}
    int top()
    {
        if (this->isEmpty() == false)
            return this->head->value;
        return 0;
    }
    bool isEmpty()
    {
        return this->head == nullptr ? true : false;
    }
    bool pop()
    {
        if (this->isEmpty() == true)
            return false;
        Node *last = this->head;
        this->head = this->head->next;
        delete last;
        return true;
    }
    void push(const int &val)
    {
        Node *node = new Node(val, this->head);
        this->head = node;
    }
}stack[MAXN * 3];
char str[256];
bool endTag;
int n, cnt[MAXN], k, temp, maxTag;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    endTag = false;
    memset(cnt, 0, sizeof(cnt));
    k = 0, maxTag = 0;
    while (scanf("%s", str))
    {
        switch (str[0])
        {
        case 'p':
            scanf("%d", &n);
            stack[++cnt[n]].push(n);
            maxTag = max(maxTag, cnt[n]);
            break;
        case 'e':
            if (stack[maxTag].isEmpty() == true)
            {
                printf("pa\n");
                break;
            }
            temp = stack[maxTag].top();
            printf("%d\n", temp);
            --cnt[temp];
            stack[maxTag].pop();
            if (stack[maxTag].isEmpty() == true)
                --maxTag;
            break;
        default:
            endTag = true;
            break;
        }
        if (endTag == true)
            break;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}