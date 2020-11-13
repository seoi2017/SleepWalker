/*
Environment: C++17
Course: SUSTech_C++
Problem ID: Project_1
*/
#include "Matrix.h"
#include "Operations.h"

#pragma GCC optimize(3, "Ofast", "inline")

// #define SAMPLE

#ifndef SAMPLE
#define ROWSA 1024
#define COLSA 1024
#define ROWSB 1024
#define COLSB 1024
#define OUTPUT_CONTROL true, false
#else
#define ROWSA 16
#define COLSA 8
#define ROWSB 8
#define COLSB 16
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
    // a.print(), b.print(), a_.print(), b_.print();
#endif
    Repeater vanilla(multiMethodVanilla, REP_TIMES, "vanilla");
    Repeater OpenBLAS(multiMethodOpenBLAS, REP_TIMES, "OpenBLAS");
    Repeater advanced(multiMethodAdvanced, REP_TIMES, "advanced");
    // Repeater testing(multiMethodTesting, REP_TIMES, "testing");
    vanilla.setArguments(a, b);
    OpenBLAS.setArguments(a, b);
    advanced.setArguments(a_, b_);
    // testing.setArguments(a, b);
    try
    {
        // vanilla.execute(OUTPUT_CONTROL);
        OpenBLAS.execute(OUTPUT_CONTROL);
        advanced.execute(OUTPUT_CONTROL);
        // testing.execute(OUTPUT_CONTROL);
    }
    catch (const char* message)
    {
        cout << "Error Detected: \033[31m" << message << "\033[0m" << endl;
    }
}

// TODO : Replace all "posix_memalign" methods to "_mm_malloc"