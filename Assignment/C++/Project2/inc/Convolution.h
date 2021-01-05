#pragma once

#include "Layer.h"

namespace myCnn
{
    class Convolution : public Layer
    {
    private:
    
        int pad;
        int stride;
        Matrix kernel;
        Matrix bias;

        int channel;

        int calcSize(const int& value) const;
        void merge();

    public:

        Convolution(const int& stride, const Matrix& kernel, const Matrix& bias, const int& pad = 0);
        
        ~Convolution();

        void setChannelDimension(const int& channel = -1);
        void execute(const Matrix& input);
        void display() const;

    };
}