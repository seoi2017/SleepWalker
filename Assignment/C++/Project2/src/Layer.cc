#include "Layer.h"

myCnn::Layer::Layer(const LayerType& type) : layerType(type) {}

myCnn::Layer::~Layer() {}

const myCnn::LayerType myCnn::Layer::getType() const
{
    return this->layerType;
}

const myCnn::Matrix myCnn::Layer::getResult() const
{
    return this->result.clone();
}

const vector<int> myCnn::Layer::getResultDimensions() const
{
    return this->result.getDimensions();
}

const int myCnn::Layer::getResultSize() const
{
    return this->result.getSize();
}

bool myCnn::Layer::isOutBound(const int& bound, const int& current) const
{
    if (current < 0 || current >= bound)
        return true;
    else
        return false;
}

bool myCnn::Layer::isLess(vector<int>& counter, const vector<int>& target) const
{
    if (counter.size() != target.size())
        throw "Invalid Dimensions during Comparison.";

    const int size = counter.size();

    for (int i = size - 1; i >= 0; --i)
        if (counter[i] == target[i] - 1)
            if (i == 0)
                return false;
            else
            {
                if (++counter[i - 1] < target[i - 1])
                {
                    counter[i] = 0;
                    return true;
                }
                return false;
            }
        else // if (counter[i] < target[i] - 1)
        {
            ++counter[i];
            return true;
        }

    throw "Unknown Error during Comparison.";
}