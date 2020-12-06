#include "Number.h"

Number::Number(const int& v) : value(v) {}

Number::Number(const Number& x) : value(x.value) {}

Number Number::operator++(int)
{
    Number result(*this);
    ++this->value;
    return result;
}

Number Number::operator++()
{
    ++this->value;
    return Number(*this);
}

Number Number::operator--(int)
{
    Number result(*this);
    --this->value;
    return result;
}

Number Number::operator--()
{
    --this->value;
    return Number(*this);
}

ostream& operator<<(ostream& os, const Number& other)
{
    os << other.value;
    return os;
}

istream& operator>>(istream& os, Number& other)
{
    os >> other.value;
    return os;
}