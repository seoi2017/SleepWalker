#include "matrix.hpp"

using del = std::default_delete<float[]>;

Matrix::Matrix() : rows(0), cols(0)
{
    this->data.reset();
}

Matrix::Matrix(shared_ptr<float> data, const intu& rows, const intu& cols) : rows(rows), cols(cols)
{
    this->data.reset(new float[rows * cols], del());
    memcpy(this->data.get(), data.get(), rows * cols * sizeof(float));
}

Matrix::Matrix(const intu& row_col) : rows(row_col), cols(row_col)
{
    this->data.reset(new float[row_col * row_col], del());
    memset(this->data.get(), 0, row_col * row_col * sizeof(float));
}

Matrix::Matrix(const intu& rows, const intu& cols) : rows(rows), cols(cols)
{
    this->data.reset(new float[rows * cols], del());
    memset(this->data.get(), 0, rows * cols * sizeof(float));
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols)
{
    this->data = other.data;
}

Matrix Matrix::getInstance(const float* data, const intu& rows, const intu& cols)
{
    shared_ptr<float> result(new float[rows * cols], del());
    memcpy(result.get(), data, rows * cols * sizeof(float));
    return Matrix(result, rows, cols);
}

Matrix::~Matrix()
{
    this->data.reset();
    this->cols = 0;
    this->rows = 0;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    if (this->rows == 0 || this->cols == 0 || other.rows == 0 || other.cols == 0)
        throw MatrixException("Invalid arguments");
    if (this->cols != other.rows)
        throw MatrixException("Unacceptable arguments");
    shared_ptr<float> a(this->data), b(other.data), c(new float[this->rows * other.cols], del());
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, this->rows, other.cols, this->cols, 1, a.get(), this->cols, b.get(), other.cols, 0, c.get(), other.cols);
    return Matrix(c, this->rows, other.cols);
}

Matrix Matrix::operator*(const float& other) const
{
    if (this->rows == 0 || this->cols == 0)
        throw MatrixException("Invalid arguments");
    intu length = this->rows * this->cols;
    shared_ptr<float> result(new float[length], del());
    for (intu i = 0; i < length; ++i)
        result.get()[i] = this->data.get()[i] * other;
    return Matrix(result, this->rows, this->cols);
}

Matrix operator*(const float& other, const Matrix& self)
{
    if (self.rows == 0 || self.cols == 0)
        throw MatrixException("Invalid arguments");
    intu length = self.rows * self.cols;
    shared_ptr<float> result(new float[length], del());
    for (intu i = 0; i < length; ++i)
        result.get()[i] = self.data.get()[i] * other;
    return Matrix(result, self.rows, self.cols);
}

Matrix Matrix::operator+(const Matrix& other) const
{
    if (this->rows == 0 || this->cols == 0 || other.rows == 0 || other.cols == 0)
        throw MatrixException("Invalid arguments");
    if (this->rows != other.rows || this->cols != other.cols)
        throw MatrixException("Unacceptable arguments");
    intu length = this->rows * this->cols;
    shared_ptr<float> result(new float[length], del());
    for (intu i = 0; i < length; ++i)
        result.get()[i] = this->data.get()[i] + other.data.get()[i];
    return Matrix(result, this->rows, this->cols);
}

Matrix Matrix::operator+(const float& other) const
{
    if (this->rows == 0 || this->cols == 0)
        throw MatrixException("Invalid arguments");
    intu length = this->rows * this->cols;
    shared_ptr<float> result(new float[length], del());
    for (intu i = 0; i < length; ++i)
        result.get()[i] = this->data.get()[i] + other;
    return Matrix(result, this->rows, this->cols);
}

Matrix operator+(const float& other, const Matrix& self)
{
    if (self.rows == 0 || self.cols == 0)
        throw MatrixException("Invalid arguments");
    intu length = self.rows * self.cols;
    shared_ptr<float> result(new float[length], del());
    for (intu i = 0; i < length; ++i)
        result.get()[i] = self.data.get()[i] + other;
    return Matrix(result, self.rows, self.cols);
}

Matrix Matrix::operator-(const Matrix& other) const
{
    if (this->rows == 0 || this->cols == 0 || other.rows == 0 || other.cols == 0)
        throw MatrixException("Invalid arguments");
    if (this->rows != other.rows || this->cols != other.cols)
        throw MatrixException("Unacceptable arguments");
    intu length = this->rows * this->cols;
    shared_ptr<float> result(new float[length], del());
    for (intu i = 0; i < length; ++i)
        result.get()[i] = this->data.get()[i] - other.data.get()[i];
    return Matrix(result, this->rows, this->cols);
}

Matrix Matrix::operator-(const float& other) const
{
    if (this->rows == 0 || this->cols == 0)
        throw MatrixException("Invalid arguments");
    intu length = this->rows * this->cols;
    shared_ptr<float> result(new float[length], del());
    for (intu i = 0; i < length; ++i)
        result.get()[i] = this->data.get()[i] - other;
    return Matrix(result, this->rows, this->cols);
}

Matrix operator-(const float& other, const Matrix& self)
{
    if (self.rows == 0 || self.cols == 0)
        throw MatrixException("Invalid arguments");
    intu length = self.rows * self.cols;
    shared_ptr<float> result(new float[length], del());
    for (intu i = 0; i < length; ++i)
        result.get()[i] = self.data.get()[i] - other;
    return Matrix(result, self.rows, self.cols);
}

Matrix Matrix::operator=(const Matrix& other)
{
    // No data copy
    this->rows = other.rows, this->cols = other.cols;
    this->data = other.data;
    return *this;
}

Matrix Matrix::operator=(const float& other)
{
    intu length = this->rows * this->cols;
    for (intu i = 0; i < length; ++i)
        this->data.get()[i] = other;
    return *this;
}

bool Matrix::operator==(const Matrix& other) const
{
    if (this->rows != other.rows || this->cols != other.cols)
        return false;
    intu length = this->rows * this->cols;
    for (intu i = 0; i < length; ++i)
        if (this->data.get()[i] != other.data.get()[i])
            return false;
    return true;
}

ostream& operator<<(ostream& os, const Matrix& self)
{
    intu length = self.rows * self.cols;
    for (intu i = 0; i < length; ++i)
    {
        os << self.data.get()[i] << ((i + 1) % self.cols == 0 ? '\n' : ' ');
    }
    return os;
}

float* Matrix::operator[](const intu& row) const
{
    if (row >= this->rows)
        throw MatrixException("Index out of bound");
    float *result = new float[this->cols];
    memcpy(result, this->data.get() + row * this->cols, this->cols * sizeof(float));
    return result;
}

float& Matrix::operator()(const intu& row, const intu& col)
{
    if (row >= this->rows || col >= this->cols)
        throw MatrixException("Index out of bound");
    return this->data.get()[row * this->cols + col];
}

Matrix Matrix::transpose()
{
    shared_ptr<float> result(new float[this->rows * this->cols], del());
    intu newRows = this->cols, newCols = this->rows;
    for (intu i = 0; i < newRows; ++i)
        for (intu j = 0; j < newCols; ++j)
            result.get()[i * newCols + j] = this->data.get()[j * newRows + i];
    return Matrix(result, this->cols, this->rows);
}

Matrix Matrix::subMatrix(const intu& startRow, const intu& startCol, const intu& rows, const intu& cols)
{
    if (startRow >= this->rows || startCol >= this->cols)
        throw MatrixException("Index out of bound");
    if (startRow + rows > this->rows || startCol + cols > this->cols)
        throw MatrixException("Index out of bound");
    shared_ptr<float> result(new float[rows * cols], del());
    for (intu i = startRow, ri = 0; i < startRow + rows; ++i, ++ri)
        for (intu j = startCol, rj = 0; j < startCol + cols; ++j, ++rj)
            result.get()[ri * cols + rj] = this->data.get()[i * this->cols + j];
    return Matrix(result, rows, cols);
}

Matrix Matrix::clone()
{
    return Matrix(this->data, this->rows, this->cols);
}

int Matrix::getRows() const
{
    return this->rows;
}

int Matrix::getCols() const
{
    return this->cols;
}

float* Matrix::getRow(const intu& row)
{
    // No need to judge, because the function operator[] will judge the argument.
    return this->operator[](row);
}

float* Matrix::getCol(const intu& col)
{
    if (col >= this->cols)
        throw MatrixException("Index out of bound");
    float *result = new float[this->rows];
    for (intu i = 0, j = col; i < this->rows; ++i, j += this->cols)
        result[i] = this->data.get()[j];
    return result;
}

Matrix Matrix::operator*=(const Matrix& other)
{
    return *this = this->operator*(other);
}

Matrix Matrix::operator*=(const float& other)
{
    return *this = this->operator*(other);
}

Matrix Matrix::operator+=(const Matrix& other)
{
    return *this = this->operator+(other);
}

Matrix Matrix::operator+=(const float& other)
{
    return *this = this->operator+(other);
}

Matrix Matrix::operator-=(const Matrix& other)
{
    return *this = this->operator-(other);
}

Matrix Matrix::operator-=(const float& other)
{
    return *this = this->operator-(other);
}