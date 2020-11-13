#pragma once

#include <bits/stdc++.h>
#include <Matrix.h>

using namespace std;

namespace myMath
{
    typedef Matrix* (*Method)(const Matrix&, const Matrix&, Timer&);

    class Repeater
    {
    private:
        Method target;
        int times;
        string name;
        Matrix *argX, *argY;
        TimeType timetype;
    public:
        Repeater(Method, const int& = 1, const string& = "default");
        void setTimeType(TimeType = MSEC);
        void setArguments(Matrix&, Matrix&);
        void execute(const bool& = true, const bool& = false);
        void setRepeatTimes(const int&);
    };

    // Other Testing Methods
    Matrix* multiMethodTesting(const Matrix&, const Matrix&, Timer&);
}