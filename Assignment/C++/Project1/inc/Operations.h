#pragma once

#include <bits/stdc++.h>
#include <Matrix.h>

using namespace std;

namespace myMath
{
    typedef Matrix *(*Method)(const Matrix &, const Matrix &, Timer &);

    class Repeater
    {
    private:
        Method target;
        int times;
        string name;
        Matrix *argX, *argY;
        TimeType timetype;

    public:
        Repeater(Method, const int & = 1, const string & = "default");
        void setTimeType(TimeType = MSEC);
        void setArguments(Matrix &, Matrix &);
        void execute(const bool & = true, const bool & = false);
        void setRepeatTimes(const int &);
    };

    // Other Testing Methods
    Matrix *methodBruteForce2D(const Matrix &, const Matrix &, Timer &);
    Matrix *methodRSITranspose(const Matrix &, const Matrix &, Timer &);
    Matrix *methodRSI_IKJ(const Matrix &, const Matrix &, Timer &);
    Matrix *methodBruteForce1D(const Matrix &, const Matrix &, Timer &);
    Matrix *methodRSI_IKJ_1D(const Matrix &, const Matrix &, Timer &);

    Matrix *methodLoopUnrolling(const Matrix &, const Matrix &, Timer &);
    Matrix *methodSSE(const Matrix &, const Matrix &, Timer &);
    Matrix *methodAVX(const Matrix &, const Matrix &, Timer &);
    Matrix *methodAVXAlignment(const Matrix &, const Matrix &, Timer &);
    Matrix *methodAVXAlignmentPacked(const Matrix &, const Matrix &, Timer &);
    Matrix *methodAVXAPOpenMP(const Matrix &, const Matrix &, Timer &);
} // namespace myMath