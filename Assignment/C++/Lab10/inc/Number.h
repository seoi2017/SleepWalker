#pragma once

#include <bits/stdc++.h>

using namespace std;

class Number
{
private:
    int value;
public:
    Number(const int& = 0);
    Number(const Number&);
    Number operator++(int);
    Number operator++();
    Number operator--(int);
    Number operator--();
    friend ostream& operator<<(ostream&, const Number&);
    friend istream& operator>>(istream&, Number&);
};