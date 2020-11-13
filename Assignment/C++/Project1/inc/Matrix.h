#pragma once

#include <bits/stdc++.h>
#include <smmintrin.h>
#include <x86intrin.h>
#include <chrono>
#include "cblas.h"
#include <omp.h>

#define MEM_ALIGN 32

using namespace std;
using namespace chrono;

namespace myMath
{
    using TimePoint = chrono::_V2::system_clock::time_point;

    class Matrix
    {
    private:
        bool aligned;
        int rows, cols;
        float *data;
    public:
        Matrix(const bool&, const int&, const int&, const bool& = false);
        Matrix(const bool&, const int&, const int&, float*&);
        ~Matrix();

        bool getAligned() const;
        int getRow() const;
        int getCol() const;
        float* getData() const;
        void print();
        Matrix* getTranspose() const;
    };

    enum TimeType
    {
        SEC,
        MSEC,
        USEC
    };

    class Timer
    {
    private:
        TimePoint start, end;
    public:
        Timer();
        void setStart();
        void setEnd();
        double getTimeInterval(const TimeType&) const;
    };

    // Original, OpenBLAS and Final Methods
    Matrix* multiMethodVanilla(const Matrix&, const Matrix&, Timer&);
    Matrix* multiMethodOpenBLAS(const Matrix&, const Matrix&, Timer&);
    Matrix* multiMethodAdvanced(const Matrix&, const Matrix&, Timer&);
}