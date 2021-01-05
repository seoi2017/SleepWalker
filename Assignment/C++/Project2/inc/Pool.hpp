#pragma once

#include "Layer.h"
#include <cmath>
#include <algorithm>
#include <iostream>

using myCnn::Matrix;

namespace myCnn
{
    enum PoolType
    {
        MAX, MIN, AVE
    };

    template <PoolType T> class Pool;

    template <PoolType P> void funcMax(Pool<P>& pool, const Matrix& data)
    {
        using std::max;

        const int dataSize = data.getSize();
        const vector<int> target = data.getDimensions();
        vector<int> counter(target.size());

        pool.result = Matrix(target, pool.calcSize(dataSize), static_cast<char>(0xCE));

        do
        {
            for (int i = 0, ti = 0; i < dataSize; i += pool.stride, ++ti)
                for (int j = 0, tj = 0; j < dataSize; j += pool.stride, ++tj)
                    for (int x = 0; x < pool.size; ++x)
                        for (int y = 0; y < pool.size; ++y)
                            if (pool.isOutBound(dataSize, i + x) == true ||
                                pool.isOutBound(dataSize, j + y) == true)
                                continue;
                            else
                                pool.result(counter, ti, tj) = max(pool.result(counter, ti, tj), data(counter, i + x, j + y));
        }
        while (pool.isLess(counter, target) == true);
    }

    template <PoolType P> void funcMin(Pool<P>& pool, const Matrix& data)
    {
        using std::min;

        const int dataSize = data.getSize();
        const vector<int> target = data.getDimensions();
        vector<int> counter(target.size());

        pool.result = Matrix(target, pool.calcSize(dataSize), static_cast<char>(0x4F));

        do
        {
            for (int i = 0, ti = 0; i < dataSize; i += pool.stride, ++ti)
                for (int j = 0, tj = 0; j < dataSize; j += pool.stride, ++tj)
                    for (int x = 0; x < pool.size; ++x)
                        for (int y = 0; y < pool.size; ++y)
                            if (pool.isOutBound(dataSize, i + x) == true ||
                                pool.isOutBound(dataSize, j + y) == true)
                                continue;
                            else
                                pool.result(counter, ti, tj) = min(pool.result(counter, ti, tj), data(counter, i + x, j + y));
        }
        while (pool.isLess(counter, target) == true);
    }

    template <PoolType P> void funcAve(Pool<P>& pool, const Matrix& data)
    {
        const int dataSize = data.getSize();
        const vector<int> target = data.getDimensions();
        vector<int> counter(target.size());

        pool.result = Matrix(target, pool.calcSize(dataSize), static_cast<char>(0x00));

        do
        {
            for (int i = 0, ti = 0; i < dataSize; i += pool.stride, ++ti)
                for (int j = 0, tj = 0; j < dataSize; j += pool.stride, ++tj)
                {
                    int sizeCount = 0;

                    for (int x = 0; x < pool.size; ++x)
                        for (int y = 0; y < pool.size; ++y)
                            if (pool.isOutBound(dataSize, i + x) == true ||
                                pool.isOutBound(dataSize, j + y) == true)
                                continue;
                            else
                                pool.result(counter, ti, tj) += data(counter, i + x, j + y), ++sizeCount;

                    pool.result(counter, ti, tj) /= static_cast<float>(sizeCount);
                }
        }
        while (pool.isLess(counter, target) == true);
    }

    template <PoolType T>
    class Pool : public Layer
    {
    private:

        typedef void (* PoolFunc)(Pool<T>&, const Matrix&);
        typename Pool<T>::PoolFunc funcPtr;

        int size;
        int stride;

        int calcSize(const int& value) const
        {
            using std::ceil;

            return static_cast<int>(ceil(static_cast<double>(value) / this->stride));
        }

        template <PoolType P> friend void funcMax(Pool<P>&, const Matrix&);
        template <PoolType P> friend void funcMin(Pool<P>&, const Matrix&);
        template <PoolType P> friend void funcAve(Pool<P>&, const Matrix&);

    public:

        Pool(const int& size, const int& stride) : myCnn::Layer(myCnn::LayerType::POOL)
        {
            this->size = size;
            this->stride = stride;

            switch (T)
            {
            case MAX:
                this->funcPtr = funcMax;
                break;
            case MIN:
                this->funcPtr = funcMin;
                break;
            case AVE:
                this->funcPtr = funcAve;
                break;
            default:
                throw "Null Type Pool Detected.";
                break;
            }
        }

        ~Pool() {}

        void execute(const Matrix& input)
        {
            this->funcPtr(*this, input);
        }

        void display() const
        {
            using std::cout, std::endl;

            cout << "Pool Layer, Info:" << endl;
            
            cout << "Type: ";
            switch (T)
            {
            case MAX:
                cout << "Maximum Pool";
                break;
            case MIN:
                cout << "Minimum Pool";
                break;
            case AVE:
                cout << "Average Pool";
                break;
            default:
                cout << "Unknown Pool";
                break;
            }
            cout << endl;

            cout << "Size: " << this->size << endl;
            cout << "Stride: " << this->stride << endl;
        }

    };
}