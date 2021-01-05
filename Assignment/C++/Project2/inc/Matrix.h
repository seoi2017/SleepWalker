#pragma once

#include <memory>
#include <vector>

using std::pair;
using std::shared_ptr;
using std::default_delete;
using std::vector;

namespace myCnn
{
    using InnerData = shared_ptr<float[]>;
    using Deleter = default_delete<float[]>;
    using Size = pair<int, int>;

    class Matrix
    {
    private:

        friend class FullyConnection;

        InnerData data = nullptr;
        vector<int> dimensions;
        int size = 0;

    public:

        Matrix() = default;
        Matrix(vector<int> dimensions, const int& size, const float* const data = nullptr);
        Matrix(vector<int> dimensions, const int& size, const char& filling);
        Matrix(const Matrix& other);

        ~Matrix();

        Matrix operator=(const Matrix& other);
        float& operator()(const vector<int>& dimensions, const int& x, const int& y) const;

        Matrix clone() const;

        bool redimension();
        vector<int> getDimensions() const;
        int getSize() const;
        void display() const;

    };
}