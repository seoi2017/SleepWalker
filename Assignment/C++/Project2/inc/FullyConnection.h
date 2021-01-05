#pragma once

#include "Layer.h"

using myCnn::Size;
using myCnn::InnerData;

namespace myCnn
{
    class FullyConnection : public Layer
    {
    private:

        Size weightSize;
        InnerData weight;

        Size biasSize;
        InnerData bias;

    public:

        FullyConnection(const InnerData& weight, const Size& weightSize, const InnerData& bias, const Size& biasSize);

        ~FullyConnection();

        const vector<int> getResultDimensions() const = delete;
        const int getResultSize() const = delete;

        void execute(const Matrix& input);
        void display() const;

    };
}