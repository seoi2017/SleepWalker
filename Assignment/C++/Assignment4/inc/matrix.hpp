#pragma once

#include <bits/stdc++.h>
#include "cblas.h"

using std::ostream;
using std::exception;
using std::shared_ptr;
using intu = unsigned int;

struct MatrixException : public exception
{
private:
    char* message;
public:
    MatrixException(const char* message) : exception()
    {
        this->message = new char[strlen(message)];
        memcpy(this->message, message, strlen(message));
    }
    const char* what() const throw()
    {
        return this->message;
    }
};

class Matrix
{
private:
    shared_ptr<float> data;
    intu rows, cols;

    Matrix(shared_ptr<float> data, const intu& rows, const intu& cols);
public:
    Matrix(); // Default constructor
    Matrix(const intu& row_col); // Square constructor
    Matrix(const intu& rows, const intu& cols); // Normal constructor
    Matrix(const Matrix& other); // Copy constructor

    static Matrix getInstance(const float* data, const intu& rows, const intu& cols); // static constructor

    ~Matrix();

    Matrix operator*(const Matrix& other) const;
    Matrix operator*(const float& other) const;
    friend Matrix operator*(const float& other, const Matrix& self);

    Matrix operator*=(const Matrix& other);
    Matrix operator*=(const float& other);

    Matrix operator+(const Matrix& other) const;
    Matrix operator+(const float& other) const;
    friend Matrix operator+(const float& other, const Matrix& self);

    Matrix operator+=(const Matrix& other);
    Matrix operator+=(const float& other);

    Matrix operator-(const Matrix& other) const;
    Matrix operator-(const float& other) const;
    friend Matrix operator-(const float& other, const Matrix& self);

    Matrix operator-=(const Matrix& other);
    Matrix operator-=(const float& other);

    Matrix operator=(const Matrix& other); // No data copy
    Matrix operator=(const float& other);

    bool operator==(const Matrix& other) const;
    
    friend ostream& operator<<(ostream& os, const Matrix& self);

    float* operator[](const intu& row) const; // New object
    float& operator()(const intu& row, const intu& col); // Can write!

    Matrix transpose();
    Matrix subMatrix(const intu& startRow, const intu& startCol, const intu& rows, const intu& cols);
    Matrix clone();

    int getCols() const;
    int getRows() const;
    float* getCol(const intu& col);
    float* getRow(const intu& row);
};