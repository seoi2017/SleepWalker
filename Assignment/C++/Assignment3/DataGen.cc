/*
Environment: C++11
Course: SUSTech_C++
Problem ID: Assignment_3
*/
#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace chrono;
constexpr int MAX_NUM = 200000000;
int main()
{
    ofstream outFile("in.io", ios::out | ios::binary);
    srand(static_cast<float>(time(0)));
    auto start = system_clock::now();
    for (int i = 0; i < MAX_NUM; ++i)
    {
        float temp = static_cast<float>(rand());
        outFile.write((char*)&temp, sizeof(temp));
    }
    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Data generator output time: " << duration.count() / static_cast<double>(1000) << " ms." << endl;
    return 0;
}