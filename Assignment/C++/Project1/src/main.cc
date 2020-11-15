/*
Environment: C++17
Course: SUSTech_C++
Problem ID: Project_1
*/
#include "Matrix.h"
#include "Operations.h"

// #define SAMPLE

#ifndef SAMPLE
#define ROWSA 1000
#define COLSA 1000
#define ROWSB 1000
#define COLSB 1000
#define OUTPUT_CONTROL true, false
#else
#define ROWSA 8
#define COLSA 16
#define ROWSB 16
#define COLSB 8
#define OUTPUT_CONTROL true, true
#endif

#define REP_TIMES 10

using namespace myMath;

int main()
{
#ifndef SAMPLE
    Matrix a(false, ROWSA, COLSA), b(false, ROWSB, COLSB), a_(true, ROWSA, COLSA), b_(true, ROWSB, COLSA);
#else
    Matrix a(false, ROWSA, COLSA, true), b(false, ROWSB, COLSB, true), a_(true, ROWSA, COLSA, true), b_(true, ROWSB, COLSB, true);
    a.print(), b.print(), a_.print(), b_.print();
#endif
    Repeater bruteForce2D(methodBruteForce2D, REP_TIMES, "brute force 2D");
    Repeater RSI2DTranspose(methodRSITranspose, REP_TIMES, "RSI 2D transpose with reference");
    Repeater RSI2DIKJ(methodRSI_IKJ, REP_TIMES, "RSI 2D with IKJ");
    Repeater bruteForce1D(methodBruteForce1D, REP_TIMES, "brute force 1D");
    Repeater RSI1DIKJ(methodRSI_IKJ_1D, REP_TIMES, "RSIT 1D with IKJ");

    Repeater loopUnrolling(methodLoopUnrolling, REP_TIMES, "basic with loop unrolling (8)");
    Repeater SSE(methodSSE, REP_TIMES, "basic with SSE");
    Repeater AVX(methodAVX, REP_TIMES, "basic with AVX");
    Repeater AVXAligned(methodAVXAlignment, REP_TIMES, "AVX with memory alignment");
    Repeater AVXAlignedPacked(methodAVXAlignmentPacked, REP_TIMES, "AVX alignment with packed");
    Repeater AVXAPOpenMP(methodAVXAPOpenMP, REP_TIMES, "AVX AP with OpenMP");

    Repeater basic(multiMethodBasic, REP_TIMES, "basic");
    Repeater advanced(multiMethodAdvanced, REP_TIMES, "advanced");
    Repeater openBLAS(multiMethodOpenBLAS, REP_TIMES, "OpenBLAS");

    bruteForce2D.setArguments(a, b);
    RSI2DTranspose.setArguments(a, b);
    RSI2DIKJ.setArguments(a, b);
    bruteForce1D.setArguments(a, b);
    RSI1DIKJ.setArguments(a, b);

    loopUnrolling.setArguments(a, b);
    SSE.setArguments(a, b);
    AVX.setArguments(a, b);
    AVXAligned.setArguments(a_, b_);
    AVXAlignedPacked.setArguments(a_, b_);
    AVXAPOpenMP.setArguments(a_, b_);

    basic.setArguments(a, b);
    advanced.setArguments(a_, b_);
    openBLAS.setArguments(a, b);

    try
    {
        /*
        bruteForce2D.execute(OUTPUT_CONTROL);
        bruteForce1D.execute(OUTPUT_CONTROL);
        RSI2DTranspose.execute(OUTPUT_CONTROL);
        RSI2DTranspose.execute(OUTPUT_CONTROL);
        RSI2DIKJ.execute(OUTPUT_CONTROL);
        */

        /*
        loopUnrolling.execute(OUTPUT_CONTROL);
        SSE.execute(OUTPUT_CONTROL);
        AVX.execute(OUTPUT_CONTROL);
        AVXAligned.execute(OUTPUT_CONTROL);
        AVXAlignedPacked.execute(OUTPUT_CONTROL);
        AVXAlignedPacked.execute(OUTPUT_CONTROL);
        AVXAPOpenMP.execute(OUTPUT_CONTROL);
        */
        
        basic.execute(OUTPUT_CONTROL);
        advanced.execute(OUTPUT_CONTROL);
        openBLAS.execute(OUTPUT_CONTROL);
    }
    catch (const char *message)
    {
        cout << "Error Detected: \033[31m" << message << "\033[0m" << endl;
    }
}

// TODO : Replace all "posix_memalign" methods to "_mm_malloc"