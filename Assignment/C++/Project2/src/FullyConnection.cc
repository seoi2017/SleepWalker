#include "FullyConnection.h"
#include <cmath>
#include <iostream>

#define RESULT_X this->biasSize.first
#define RESULT_Y this->biasSize.second

using myCnn::Matrix;
using std::exp;

myCnn::FullyConnection::FullyConnection(
    const InnerData& weight,
    const Size& weightSize,
    const InnerData& bias,
    const Size& biasSize
) : myCnn::Layer(myCnn::LayerType::FCNT)
{
    if (weightSize.first != biasSize.first)
        throw "Bias is Mismatched to Weight.";

    this->weight = weight;
    this->weightSize = weightSize;
    this->bias = bias;
    this->biasSize = biasSize;
}

myCnn::FullyConnection::~FullyConnection() {}

void myCnn::FullyConnection::execute(const Matrix& input)
{
    const vector<int> inDim = input.getDimensions();
    int inSize = input.getSize() * input.getSize();
    for (int dim : inDim)
        inSize *= dim;
    if (inSize != this->weightSize.second)
        throw "InnerData Mismatched.";

    const myCnn::InnerData& data = input.data;

    this->result = Matrix({RESULT_X, RESULT_Y}, 1);
    for (int x = 0; x < RESULT_X; ++x)
        for (int y = 0; y < this->weightSize.second; ++y)
            for (int z = 0; z < RESULT_Y; ++z)
                this->result({x, z}, 0, 0) += data[y * RESULT_Y + z] * this->weight[x * this->weightSize.second + y];

    for (int i = 0; i < RESULT_X; ++i)
        for (int j = 0; j < RESULT_Y; ++j)
            this->result({i, j}, 0, 0) += this->bias[i * RESULT_Y + j];

    // Softmax Process
    float sigmaX = 0.0F;
    for (int i = 0; i < RESULT_X; ++i)
        for (int j = 0; j < RESULT_Y; ++j)
            sigmaX += exp(this->result({i, j}, 0, 0));
    for (int i = 0; i < RESULT_X; ++i)
        for (int j = 0; j < RESULT_Y; ++j)
            this->result({i, j}, 0, 0) = exp(this->result({i, j}, 0, 0)) / sigmaX;
}

void myCnn::FullyConnection::display() const
{
    using std::cout, std::endl;

    cout << "Fully Connection Layer, Info:" << endl;
    cout << "Size of Weight Matrix: " << this->weightSize.first << "*" << this->weightSize.second << endl;
    cout << "Size of Bias Matrix: " << this->biasSize.first << "*" << this->biasSize.second << endl;
}