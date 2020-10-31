/*
Author: Invrise
OJ Site: SUSTech_DSAA_OJ
Problem ID: Lab4_H
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
template<class T>
class List
{
public:
    struct Node
    {
    private:
        Node *prev, *next;
        T val;
    public:
        Node(Node *copy)
        {
            this->prev = copy->prev;
            this->next = copy->next;
            this->val = copy->val;
        }
        Node(T value = T(), Node *prev = nullptr, Node *next = nullptr): val(value), prev(prev), next(next) {}
        void setPrev(Node *prev)
        {
            this->prev = prev;
        }
        Node* getPrev()
        {
            return this->prev;
        }
        void setNext(Node *next)
        {
            this->next = next;
        }
        Node* getNext()
        {
            return this->next;
        }
        void setValue(T value)
        {
            this->val = value;
        }
        T getValue()
        {
            return this->val;
        }
    };
private:
    int size;
    Node *beginPtr, *endPtr;
    bool connect(Node *before, Node *after)
    {
        if (before == nullptr || after == nullptr)
            return false;
        before->setNext(after);
        after->setPrev(before);
        return true;
    }
public:
    List()
    {
        this->size = 0;
        this->beginPtr = new Node();
        this->endPtr = new Node();
        this->connect(this->beginPtr, this->endPtr);
    }
    Node* begin()
    {
        return this->beginPtr;
    }
    Node *end()
    {
        return this->endPtr;
    }
    Node* push_back(T value)
    {
        return this->insert(this->endPtr->getPrev(), value);
    }
    Node* push_front(T value)
    {
        return this->insert(this->beginPtr, value);
    }
    Node* erase(Node* node)
    {
        if (node == nullptr || node == this->beginPtr || node == this->endPtr)
            return nullptr;
        connect(node->getPrev(), node->getNext());
        --this->size;
        return node->getNext();
    }
    Node* insert(Node *pos, T value)
    {
        if (pos == nullptr)
            return nullptr;
        Node *node = new Node(value);
        connect(node, pos->getNext());
        connect(pos, node);
        ++this->size;
        return node;
    }
    int getSize()
    {
        return this->size;
    }
    void print()
    {
        Node *it = this->beginPtr;
        do
        {
            printf("%d, ", it->getValue());
            it = it->getNext();
        }
        while (it != nullptr);
        printf("\n");
    }
};
int n, m;
char ope;
List<int> lst;
List<int>::Node *it;
int main()
{
#ifdef LOCAL
    freopen("in.io", "r", stdin);
    freopen("out.io", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 0, temp; i < n; ++i)
    {
        scanf("%d", &temp);
        lst.push_back(temp);
    }
    for (int i = 0, j, arg1, arg2; i < m; ++i)
    {
        scanf("\n%c%d", &ope, &arg1);
        switch (ope)
        {
        case 'i':
            scanf("%d", &arg2);
            it = lst.begin();
            for (j = 0; j < arg1 - 1; ++j)
                it = it->getNext();
            lst.insert(it, arg2);
            break;
        case 'q':
            it = lst.begin();
            for (j = 0; j < arg1; ++j)
                it = it->getNext();
            printf("%d\n", it->getValue());
            break;
        case 'r':
            it = lst.begin();
            for (j = 0; j < arg1; ++j)
                it = it->getNext();
            lst.erase(it);
            break;
        default:
            break;
        }
        // lst.print();
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}