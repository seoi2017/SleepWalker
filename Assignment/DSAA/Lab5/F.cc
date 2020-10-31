/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab5_F
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAXN 3000010
using namespace std;
int n, k, ans, val[MAXN];
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
    int back()
    {
        if (this->isEmpty() == true)
            return -1;
        return this->tail->val;
    }
    int front()
    {
        if (this->isEmpty() == true)
            return -1;
        return this->head->val;
    }
    void clear()
    {
        while (this->size > 0)
            this->pop_back();
    }
}inc, des;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d%d", &k, &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &val[i]);
    ans = 0;
    for (int l = 0, r = 0; r < n; ++r)
    {
        while (inc.isEmpty() == false && val[inc.back()] > val[r])
            inc.pop_back();
        inc.push_back(r);
        while (des.isEmpty() == false && val[des.back()] < val[r])
            des.pop_back();
        des.push_back(r);
        while (val[des.front()] - val[inc.front()] > k)
        {
            while (inc.isEmpty() == false && inc.front() <= l)
                inc.pop_front();
            while (des.isEmpty() == false && des.front() <= l)
                des.pop_front();
            ++l;
        }
        ans = max(ans, r - l + 1);
    }
    printf("%d\n", ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}