#include "ReLU.h"
#include <cmath>
#include <iostream>

myCnn::ReLU::ReLU(const float& limit) : myCnn::Layer(myCnn::LayerType::RELU)
{
    this->limit = limit;
}

myCnn::ReLU::~ReLU() {}

void myCnn::ReLU::execute(const Matrix& input)
{
    using std::max;

    const int dataSize = input.getSize();
    const vector<int> target = input.getDimensions();
    vector<int> counter(target.size());

    this->result = Matrix(target, dataSize);

    do
    {
        for (int i = 0; i < dataSize; ++i)
            for (int j = 0; j < dataSize; ++j)
                this->result(counter, i, j) = max(this->limit, input(counter, i, j));
    }
    while (this->isLess(counter, target) == true);
}

void myCnn::ReLU::display() const
{
    using std::cout, std::endl;

    cout << "Rectified Linear Unit Layer, Info:" << endl;
    cout << "Limit: " << this->limit << endl;
}