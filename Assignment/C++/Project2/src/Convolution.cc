#include "Convolution.h"
#include <cmath>
#include <cfloat>
#include <iostream>

myCnn::Convolution::Convolution(
    const int& stride,
    const Matrix& kernel,
    const Matrix& bias,
    const int& pad
) : myCnn::Layer(myCnn::LayerType::CONV)
{
    this->stride = stride;
    this->kernel = kernel;
    this->pad = pad;

    if (bias.getSize() == 0 || bias.getSize() == 1)
        this->bias = bias;
    else
        throw "Wrong Bias Format.";

    this->channel = -1;
}

myCnn::Convolution::~Convolution() {}

int myCnn::Convolution::calcSize(const int& value) const
{
    using std::ceil, std::abs;

    const int totSize = this->pad * 2 + value;
    const int kernelSize = this->kernel.getSize();

    return static_cast<int>(abs(totSize - kernelSize) / this->stride) + 1;
}

void myCnn::Convolution::merge()
{
    if (this->channel == -1)
        return;

    const int dataSize = this->result.getSize();
    const int offset = this->kernel.getDimensions()[this->channel];
    const vector<int> target = this->result.getDimensions();
    vector<int> newTarget = target;
    vector<int> counter(target.size());

    newTarget[this->channel] = 1;
    Matrix newResult(newTarget, dataSize);

    auto isFit = [&offset](const int& value) -> bool
    {
        for (int i = 0; i < offset; ++i)
            if (value == offset * i + i)
                return true;
        return false;
    };
    
    do
    {
        newTarget = counter;
        if (isFit(newTarget[this->channel]) == false)
            continue;
        else
            newTarget[this->channel] = 0;

        for (int i = 0; i < dataSize; ++i)
            for (int j = 0; j < dataSize; ++j)
                newResult(newTarget, i, j) += this->result(counter, i, j);
    }
    while (this->isLess(counter, target) == true);

    this->result = newResult;
}

void myCnn::Convolution::setChannelDimension(const int& channel)
{
    const int totDimensions = this->kernel.getDimensions().size();

    if ((channel < 0 || channel >= totDimensions) && channel != -1)
        throw "Channel out of Bound.";
    else
        this->channel = channel;
}

void myCnn::Convolution::execute(const Matrix& input)
{
    const vector<int> target = input.getDimensions();
    const vector<int> dimKernel = this->kernel.getDimensions();

    if (target.size() != dimKernel.size())
        throw "Unmatched Dimensions.";
    if (target[this->channel] != dimKernel[this->channel])
        throw "Unmatched Merging Channel.";

    const int dataSize = input.getSize();
    const int kernelSize = this->kernel.getSize();
    const int finalSize = this->calcSize(dataSize);
    vector<int> kernelCounter(dimKernel.size());
    vector<int> dataCounter(target.size());

    vector<int> newTarget = target;
    for (size_t i = 0; i < target.size(); ++i)
        newTarget[i] *= dimKernel[i];
    vector<int> counter(newTarget.size());
    this->result = Matrix(newTarget, finalSize);
    
    do
    {
        dataCounter = vector<int>(target.size());
        do
        {
            for (int i = 0 - this->pad, ti = 0; i < dataSize + this->pad; i += this->stride, ++ti)
                for (int j = 0 - this->pad, tj = 0; j < dataSize + this->pad; j += this->stride, ++tj)
                {
                    // int sizeCount = 0;
                    float answer = 0.0F;

                    for (int x = 0; x < kernelSize; ++x)
                        for (int y = 0; y < kernelSize; ++y)
                            if (this->isOutBound(dataSize, i + x) == true ||
                                this->isOutBound(dataSize, j + y) == true)
                                continue;
                            else
                            {
                                answer += this->kernel(kernelCounter, x, y) * input(dataCounter, i + x, j + y);
                                // ++sizeCount;
                            }

                    if (this->isOutBound(finalSize, ti) == false && this->isOutBound(finalSize, tj) == false)
                    {
                        if (std::abs(answer) < FLT_EPSILON)
                            answer = 0.0F;

                        this->result(counter, ti, tj) = answer /* / static_cast<float>(sizeCount) */ ;
                    }
                }

            this->isLess(counter, newTarget);
        }
        while (this->isLess(dataCounter, target) == true);
    }
    while (this->isLess(kernelCounter, dimKernel) == true);

    this->merge();

    const vector<int> finalTarget = this->result.getDimensions();
    vector<int> newCounter(finalTarget.size());

    do
    {
        if (this->bias.getSize() == 0)
            break;

        for (int x = 0; x < finalSize; ++x)
            for (int y = 0; y < finalSize; ++y)
                try
                {
                    this->result(newCounter, x, y) += this->bias(newCounter, 0, 0);
                }
                catch (const char* error)
                {
                    throw "Bias Mismatched.";
                }
    }
    while (this->isLess(newCounter, finalTarget) == true);
}

void myCnn::Convolution::display() const
{
    using std::cout, std::endl;

    cout << "Convolution Layer, Info:" << endl;
    cout << "Pad: " << this->pad << endl;
    cout << "Stride: " << this->stride << endl;
    cout << "Kernel:" << endl;
    this->kernel.display();
    cout << "Bias:" << endl;
    this->bias.display();
}