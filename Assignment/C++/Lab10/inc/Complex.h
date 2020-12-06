#pragma once

#include <bits/stdc++.h>

using namespace std;

class Complex
{
private:
    double real, imaginary;
public:
    Complex(const Complex&);
    Complex(const double& = 0, const double& = 0);
    friend ostream& operator<<(ostream&, const Complex&);
    friend istream& operator>>(istream&, Complex&);
    Complex operator~() const;
    Complex operator+(const Complex&) const;
    Complex operator-(const Complex&) const;
    Complex operator*(const Complex&) const;
    Complex operator/(const Complex&) const;
    Complex operator=(const Complex&);
    friend Complex operator+(const double&, const Complex&);
    friend Complex operator+(const Complex&, const double&);
    friend Complex operator*(const double&, const Complex&);
    friend Complex operator*(const Complex&, const double&);
    bool operator==(const Complex&) const;
    bool operator!=(const Complex&) const;
};