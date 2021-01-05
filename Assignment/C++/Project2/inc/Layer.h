#pragma once

#include "Matrix.h"
#include <vector>

using std::vector;

namespace myCnn
{
    enum LayerType
    {
        CONV, RELU, POOL, FCNT
    };

    class Layer
    {
    private:

        LayerType layerType;

    protected:

        Matrix result;

        bool isOutBound(const int& bound, const int& current) const;
        bool isLess(vector<int>& counter, const vector<int>& target) const;

    public:

        Layer(const LayerType& type);

        virtual ~Layer();

        virtual void execute(const Matrix&) = 0;
        virtual void display() const = 0;

        const LayerType getType() const;
        const Matrix getResult() const;
        const vector<int> getResultDimensions() const;
        const int getResultSize() const;

    };
}