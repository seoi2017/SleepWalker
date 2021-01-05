#include "Matrix.h"

#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

myCnn::Matrix::Matrix(
    vector<int> dimensions,
    const int& size,
    const float* const data
) : size(size)
{
    int totSize = size * size;

    for (int arg : dimensions)
    {
        this->dimensions.push_back(arg);
        totSize *= arg;
    }

    this->data = myCnn::InnerData(new float[totSize](), myCnn::Deleter());
    if (data != nullptr)
        memcpy(this->data.get(), data, totSize * sizeof(float));
}

myCnn::Matrix::Matrix(
    vector<int> dimensions,
    const int& size,
    const char& filling
) : size(size)
{
    int totSize = size * size;

    for (int arg : dimensions)
    {
        this->dimensions.push_back(arg);
        totSize *= arg;
    }

    this->data = myCnn::InnerData(new float[totSize](), myCnn::Deleter());
    memset(this->data.get(), filling, totSize * sizeof(float));
}

myCnn::Matrix::Matrix(const Matrix& other)
{
    this->size = other.size;
    this->data = other.data;
    this->dimensions = other.dimensions;
}

myCnn::Matrix::~Matrix()
{
    this->dimensions.clear();
}

myCnn::Matrix myCnn::Matrix::operator=(const myCnn::Matrix& other)
{
    this->size = other.size;
    this->data = other.data;
    this->dimensions = other.dimensions;
    return Matrix(*this);
}

float& myCnn::Matrix::operator()(
    const vector<int>& dimensions,
    const int& x,
    const int& y
) const
{
    if (dimensions.size() != this->dimensions.size())
        throw "Unmatched Dimensions.";
    if (x >= this->size || y >= this->size || x < 0 || y < 0)
        throw "Position out of Bound.";

    int pos = x * this->size + y;
    int offset = this->size * this->size;
    for (int i = (dimensions.size() - 1); i >= 0; --i)
        if (dimensions[i] < 0 || dimensions[i] >= this->dimensions[i])
            throw "Illegal Dimensions.";
        else
        {
            pos += dimensions[i] * offset;
            offset *= this->dimensions[i];
        }
    
    return this->data[pos];
}

myCnn::Matrix myCnn::Matrix::clone() const
{
    return Matrix(this->dimensions, this->size, this->data.get());
}

bool myCnn::Matrix::redimension()
{
    if (this->dimensions.size() == 0 || *this->dimensions.rbegin() > 1)
        return false;
    
    this->dimensions.insert(this->dimensions.begin(), *this->dimensions.rbegin());
    this->dimensions.pop_back();

    return true;
}

vector<int> myCnn::Matrix::getDimensions() const
{
    return this->dimensions;
}

int myCnn::Matrix::getSize() const
{
    return this->size;
}

void myCnn::Matrix::display() const
{
    cout << "Matrix properties:" << endl;

    cout << "Dimensions: ";
    size_t count = 0;
    for (int dim : this->dimensions)
    {
        cout << dim;
        if (++count != this->dimensions.size())
            cout << "*";
        else
            cout << endl;
    }

    cout << "Size: " << this->size << "*" << this->size << endl;
}