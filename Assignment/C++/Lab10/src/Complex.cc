#include "Complex.h"

Complex::Complex(const Complex& x) : real(x.real), imaginary(x.imaginary) {}

Complex::Complex(const double& r, const double& s) : real(r), imaginary(s) {}

Complex Complex::operator~() const
{
    return Complex(this->real, -1.0 * this->imaginary);
}

Complex Complex::operator+(const Complex& x) const
{
    return Complex(this->real + x.real, this->imaginary + x.imaginary);
}

Complex Complex::operator-(const Complex& x) const
{
    return Complex(this->real - x.real, this->imaginary - x.imaginary);
}

Complex Complex::operator*(const Complex& x) const
{
    double r = this->real * x.real + -1.0 * this->imaginary * x.imaginary;
    double s = this->real * x.imaginary + this->imaginary * x.real;
    return Complex(r, s);
}

Complex Complex::operator/(const Complex& x) const
{
    return this->operator*(~x);
}

Complex Complex::operator=(const Complex& x)
{
    this->real = x.real;
    this->imaginary = x.imaginary;
    return Complex(*this);
}

ostream& operator<<(ostream& os, const Complex& other)
{
    os << other.real << "+" << other.imaginary << "i";
    return os;
}

istream& operator>>(istream& os, Complex& other)
{
    os >> other.real >> other.imaginary;
    return os;
}

Complex operator+(const double& a, const Complex& b)
{
    return Complex(a + b.real, b.imaginary);
}

Complex operator+(const Complex& b, const double& a)
{
    return Complex(a + b.real, b.imaginary);
}

Complex operator*(const double& a, const Complex& b)
{
    return Complex(a * b.real, a * b.imaginary);
}

Complex operator*(const Complex& b, const double& a)
{
    return Complex(a * b.real, a * b.imaginary);
}

bool Complex::operator==(const Complex& x) const
{
    return this->real == x.real && this->imaginary == x.imaginary;
}

bool Complex::operator!=(const Complex& x) const
{
    return this->real != x.real || this->imaginary != x.imaginary;
}