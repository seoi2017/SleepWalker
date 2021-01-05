/*
Environment: C++17
Course: SUSTech_C++
Problem ID: Lab13_Excerise2
*/
#include <bits/stdc++.h>
using namespace std;
template<class T, int rows, int cols>
class Matrix
{
private:
    T data[rows][cols];
    int row, col;
public:
    Matrix() : row(rows), col(cols) {}
    Matrix(T newData[rows][cols]) : row(rows), col(cols)
    {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                this->data[i][j] = newData[i][j];
    }
    Matrix<T, rows, cols> operator+(const Matrix& other) const
    {
        if (this->row != other.row || this->col != other.col)
            throw "Illegal Operations!";
        T newData[rows][cols];
        for (int i = 0; i < this->row; ++i)
            for (int j = 0; j < this->col; ++j)
                newData[i][j] = this->data[i][j] + other.data[i][j];
        return Matrix<T, rows, cols>(newData);
    }

    template<class nT, int nrows, int ncols>
    friend ostream& operator<<(ostream& os, const Matrix<nT, nrows, ncols>& other);
};

template<class T, int rows, int cols>
ostream& operator<<(ostream& os, const Matrix<T, rows, cols>& other)
{
    for (int i = 0; i < rows; ++i, cout << endl)
        for (int j = 0; j < cols; ++j)
            os << other.data[i][j] << " ";
    return os;
}

int main()
{
    int a[2][3] = {
        {1, 2, 3},
        {4, 5, 6},
    }, b[2][3] = {
        {6, 5, 4},
        {3, 2, 1},
    };
    Matrix<int, 2, 3> ma(a), mb(b);
    cout << (ma + mb) << endl;

    string sa[2][3] = {
        {"A", "B", "C"},
        {"D", "E", "F"}
    }, sb[2][3] = {
        {"A", "B", "C"},
        {"D", "E", "F"},
    };
    Matrix<string, 2, 3> msa(sa), msb(sb);
    cout << (msa + msb) << endl;

    return 0;
}