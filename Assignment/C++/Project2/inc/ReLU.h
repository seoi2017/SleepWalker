#pragma once

#include "Layer.h"

using myCnn::Matrix;

namespace myCnn
{
    class ReLU : public Layer
    {
    private:

        float limit;

    public:

        ReLU(const float& limit = 0);

        ~ReLU();

        void execute(const Matrix& input);
        void display() const;

    };
}