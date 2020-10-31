/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab5_C
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 100010
using namespace std;
class Deque
{
private:
    struct Node
    {
        int val;
        Node *prev, *next;
        Node(int value, Node *prev = nullptr, Node *next = nullptr): val(value), prev(prev), next(next) {}
        void link(Node *prev, Node *next)
        {
            this->prev = prev;
            this->next = next;
            if (this->prev != nullptr)
                this->prev->next = this;
            if (this->next != nullptr)
                this->next->prev = this;
        }
    }*head, *tail;
    int size;
public:
    Deque(): head(nullptr), tail(nullptr) {}
    bool isEmpty()
    {
        return this->size == 0 ? true : false;
    }
    void push_front(const int &x)
    {
        Node *temp = new Node(x);
        temp->link(nullptr, this->head);
        this->head = temp;
        if (++this->size == 1)
            this->tail = temp;
    }
    void push_back(const int &x)
    {
        Node *temp = new Node(x);
        temp->link(this->tail, nullptr);
        this->tail = temp;
        if (++this->size == 1)
            this->head = temp;
    }
    int pop_front()
    {
        if (this->isEmpty() == true)
            return -1;
        int result = this->head->val;
        Node *dead = this->head;
        this->head = this->head->next;
        delete dead;
        if (--this->size == 0)
            this->tail = nullptr;
        else if (this->head != nullptr)
            this->head->prev = nullptr;
        return result;
    }
    int pop_back()
    {
        if (this->isEmpty() == true)
            return -1;
        int result = this->tail->val;
        Node *dead = this->tail;
        this->tail = this->tail->prev;
        delete dead;
        if (--this->size == 0)
            this->head = nullptr;
        else if (this->tail != nullptr)
            this->tail->next = nullptr;
        return result;
    }
    void connect(Deque &x, bool reverse)
    {
        if (x.isEmpty() == true)
            return;
        if (reverse == false)
            for (Node *it = x.head; it != nullptr; it = it->next)
                this->push_back(it->val);
        else
            for (Node *it = x.tail; it != nullptr; it = it->prev)
                this->push_back(it->val);
        x.clear();
    }
    void clear()
    {
        while (this->size > 0)
            this->pop_back();
    }
}deque[MAXN];
int n, m, ope, ind, isReverse, val;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    while (scanf("%d%d", &n, &m) != EOF)
    {
        for (int i = 0; i < n; ++i)
            deque[i].clear();
        while (m--)
        {
            scanf("%d%d%d", &ope, &ind, &isReverse);
            --ind;
            switch (ope)
            {
            case 1:
                scanf("%d", &val);
                isReverse == 0 ? deque[ind].push_front(val) : deque[ind].push_back(val);
                break;
            case 2:
                printf("%d\n", isReverse == 0 ? deque[ind].pop_front() : deque[ind].pop_back());
                break;
            case 3:
                scanf("%d", &val);
                swap(val, isReverse);
                --val;
                deque[ind].connect(deque[val], isReverse == 0 ? false : true);
                break;
            default:
                break;
            }
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}