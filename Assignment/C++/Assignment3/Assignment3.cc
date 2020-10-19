/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Assignment_3
*/
// #pragma GCC optimize (3)
#include <bits/stdc++.h>
#include <smmintrin.h>
#include <x86intrin.h>
#include <chrono>
#include "omp.h"
#include "cblas.h"
using namespace std;
using namespace chrono;
constexpr int MAX_NUM = 200000000;
float *vectorFloat = new float[MAX_NUM];
inline void dataGen()
{
    ofstream outFile("in.io", ios::out | ios::binary);
    srand(static_cast<float>(time(0)));
    float *temp = new float[MAX_NUM];
    auto start = system_clock::now();
    for (int i = 0; i < MAX_NUM; ++i)
        temp[i] = static_cast<float>(rand());
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Data generation time: " << duration.count() / static_cast<double>(1000) << " ms." << endl;
    start = system_clock::now();
    outFile.write((char*)temp, MAX_NUM * sizeof(float));
    end = system_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "Data output time: " << duration.count() / static_cast<double>(1000) << " ms." << endl;
    outFile.close();
    delete[] temp;
}
inline void solveVanilla()
{
    float result = static_cast<float>(0);
    auto start = system_clock::now();
    int i = 0;
    for (i = 0; i < MAX_NUM; ++i)
        result += vectorFloat[i] * vectorFloat[i];
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Vanilla operation time: " << duration.count() / static_cast<double>(1000) << " ms." << endl;
}
inline void solveSSE()
{
    float result = static_cast<float>(0), temp[4];
    const int mask = 0xFF;
    auto start = system_clock::now();
    for (register int i = 0; i < MAX_NUM; i += 4)
    {
        _mm_storeu_ps(temp, _mm_dp_ps(_mm_loadu_ps(vectorFloat + i), _mm_loadu_ps(vectorFloat + i), mask));
        result += (temp[0] + temp[1] + temp[2] + temp[3]);
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "SSE operation time: " << duration.count() / static_cast<double>(1000) << " ms." << endl;
}
inline void solveAVX()
{
    float result = static_cast<float>(0), temp[8];
    const int mask = 0xFF;
    auto start = system_clock::now();
    for (register int i = 0; i < MAX_NUM; i += 8)
    {
        _mm256_storeu_ps(temp, _mm256_dp_ps(_mm256_loadu_ps(vectorFloat + i), _mm256_loadu_ps(vectorFloat + i), mask));
        result += (temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7]);
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "AVX operation time: " << duration.count() / static_cast<double>(1000) << " ms." << endl;
}
inline void solveOpenMP()
{
    float result = static_cast<float>(0);
    int i = 0;
    auto start = system_clock::now();
    #pragma omp parallel for shared(vectorFloat) private(i) reduction(+:result)
    for (i = 0; i < MAX_NUM; ++i)
    {
        result = result + (vectorFloat[i] * vectorFloat[i]);
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "OpenMP operation time: " << duration.count() / static_cast<double>(1000) << " ms." << endl;
}
inline void solveOpenMP_SSE()
{
    float result = static_cast<float>(0), temp[4];
    const int mask = 0xFF;
    int i = 0;
    auto start = system_clock::now();
    #pragma omp parallel for shared(vectorFloat) private(i, temp) reduction(+:result)
    for (i = 0; i < MAX_NUM; i += 4)
    {
        _mm_storeu_ps(temp, _mm_dp_ps(_mm_loadu_ps(vectorFloat + i), _mm_loadu_ps(vectorFloat + i), mask));
        result += (temp[0] + temp[1] + temp[2] + temp[3]);
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "OpenMP & SSE operation time: " << duration.count() / static_cast<double>(1000) << " ms." << endl;
}
inline void solveOpenMP_AVX()
{
    float result = static_cast<float>(0), temp[8];
    const int mask = 0xFF;
    int i = 0;
    auto start = system_clock::now();
    #pragma omp parallel for shared(vectorFloat) private(i, temp) reduction(+:result)
    for (i = 0; i < MAX_NUM; i += 8)
    {
        _mm256_storeu_ps(temp, _mm256_dp_ps(_mm256_loadu_ps(vectorFloat + i), _mm256_loadu_ps(vectorFloat + i), mask));
        result += (temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7]);
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "OpenMP & AVX operation time: " << duration.count() / static_cast<double>(1000) << " ms." << endl;
}
inline void solveOpenBLAS()
{
    float result = static_cast<float>(0);
    auto start = system_clock::now();
    result = cblas_sdot(MAX_NUM, vectorFloat, 1, vectorFloat, 1);
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "OpenBLAS operation time: " << duration.count() / static_cast<double>(1000) << " ms." << endl;
}
int main()
{
    dataGen();
    ifstream inFile("in.io", ios::in | ios::binary);
    auto start = system_clock::now();
    inFile.read((char*)vectorFloat, MAX_NUM * sizeof(float));
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Data input time: " << duration.count() / static_cast<double>(1000) << " ms." << endl;
    solveVanilla();
    solveSSE();
    solveAVX();
    solveOpenMP();
    solveOpenMP_SSE();
    solveOpenMP_AVX();
    solveOpenBLAS();
    return 0;
}