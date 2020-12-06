/*
Environment: C++17
Course: SUSTech_C++
Problem ID: Lab11_Excerise2
*/
#include <bits/stdc++.h>

using namespace std;

using Item = unsigned long long;

class Stack
{
private:
    enum {MAX = 10};
    Item* pitems;
    int size, top;
public:
    Stack(const int N = MAX) : size(N), top(0)
    {
        this->pitems = new Item[N];
    }
    Stack(const Stack& st) : size(st.size), top(st.top)
    {
        this->pitems = new Item[st.size];
        memcpy(this->pitems, st.pitems, st.size * sizeof(Item));
    }
    ~Stack()
    {
        delete this->pitems;
    }
    bool isEmpty() const
    {
        return this->top == 0;
    }
    bool isFull() const
    {
        return this->top == this->size;
    }
    bool push(const Item& item)
    {
        if (this->isFull() == true)
            return false;
        this->pitems[this->top++] = item;
        return true;
    }
    bool pop(Item& item)
    {
        if (this->isEmpty() == true)
            return false;
        item = this->pitems[--this->top];
        return true;
    }
    Stack& operator=(const Stack& st)
    {
        if (this->pitems != nullptr)
            delete this->pitems;
        this->size = st.size;
        this->top = st.top;
        this->pitems = new Item[st.size];
        memcpy(this->pitems, st.pitems, st.size * sizeof(Item));
        return *this;
    }
};
int main()
{
    Stack _1;
    for (int i = 0; i < 11; ++i)
        cout << "Push in No." << i << ": " << _1.push(i) << endl;
    Stack _2(_1), _3 = _1, *_4 = new Stack, *_5 = new Stack(_1);
    for (Item i = 0, temp; i < 11; ++i)
        cout << "Pop out No." << i << ": " << _1.pop(temp) << ", Value is: " << temp << endl;
    return 0;
}