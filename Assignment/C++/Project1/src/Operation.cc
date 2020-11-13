#include "Operations.h"

myMath::Repeater::Repeater(Method func, const int &t, const string &str) : target(func), times(t), name(str)
{
    this->argX = nullptr;
    this->argY = nullptr;
    this->timetype = TimeType::MSEC;
}

void myMath::Repeater::setTimeType(TimeType type)
{
    this->timetype = type;
}

void myMath::Repeater::setArguments(Matrix &x, Matrix &y)
{
    this->argX = &x;
    this->argY = &y;
}

void myMath::Repeater::execute(const bool &outputInformation, const bool &outputResult)
{
    if (this->argX == nullptr || this->argY == nullptr)
        throw "Null Arguments Error";
    vector<Timer> durationList;
    Matrix *result = nullptr;
    for (int i = 0; i < this->times; ++i)
    {
        Timer duration;
        free(result);
        result = this->target(*this->argX, *this->argY, duration);
        if (outputInformation == true)
        {
            cout << "Execute \033[33m" + this->name + "\033[0m method, times \033[35m" << (i + 1) << "\033[0m, time cost: ";
            cout << "\033[34m" << duration.getTimeInterval(this->timetype) << "\033[0m";
            switch (this->timetype)
            {
            case SEC:
                cout << " sec.";
                break;
            case MSEC:
                cout << " ms.";
                break;
            case USEC:
                cout << " us.";
                break;
            default:
                throw "Invalid Time Type";
            }
            cout << endl;
        }
        durationList.push_back(duration);
    }
    if (outputInformation == true)
    {
        double meanValue = 0.0;
        for (auto duration : durationList)
            meanValue += duration.getTimeInterval(this->timetype);
        cout << "Average time cost of \033[33m" << this->name << "\033[0m method: \033[32m" << meanValue / this->times << "\033[0m";
        switch (this->timetype)
        {
        case SEC:
            cout << " sec.";
            break;
        case MSEC:
            cout << " ms.";
            break;
        case USEC:
            cout << " us.";
            break;
        default:
            throw "Invalid Time Type";
        }
        cout << endl;
    }
    if (outputResult == true)
        result->print();
    free(result);
}

void myMath::Repeater::setRepeatTimes(const int &t)
{
    this->times = t;
}

myMath::Matrix* myMath::multiMethodTesting(const Matrix &x, const Matrix &y, Timer &counter)
{
    // Illegal Checking
    if (x.getAligned() == false || y.getAligned() == false)
        throw "The matrix should be aligned";
    if (x.getCol() != y.getRow())
        throw "Invalid Argument Matrices";
    int rows = x.getRow(), cols = y.getCol(), temp = x.getCol();
    if (rows % 8 != 0 || cols % 8 != 0 || temp % 8 != 0)
        throw "Matrices' size must be divisible by 8";
    // Variables Definition
    Matrix *transY = y.getTranspose();
    float *data = nullptr, *xData = x.getData(), *yData = transY->getData();
    cols = transY->getRow();
    posix_memalign((void**)&data , MEM_ALIGN, rows * cols * sizeof(float));
    float *pack = nullptr;
    if (posix_memalign((void**)&pack, MEM_ALIGN, 8 * temp * sizeof(float)) != 0)
        throw "Memory Error";
    // Working Block
    counter.setStart();
    {
        // omp_set_dynamic(0);
        auto getPackage = [&](const int &j, float *output) -> void
        {
            for (int i = 0; i < temp; ++i)
                memcpy(output + i * 8, yData + i * cols + j, sizeof(float) * 8);
        };
        auto calcPack = [&](float *dataA, float *dataB, float *dataOut) -> void
        {
            __m256 out0 = _mm256_setzero_ps();
            __m256 out1 = _mm256_setzero_ps();
            __m256 out2 = _mm256_setzero_ps();
            __m256 out3 = _mm256_setzero_ps();
            __m256 out4 = _mm256_setzero_ps();
            __m256 out5 = _mm256_setzero_ps();
            __m256 out6 = _mm256_setzero_ps();
            __m256 out7 = _mm256_setzero_ps();
            float *ptr = dataB;
            for (register int k = 0; k < temp; ++k)
            {
                __m256 in0 = _mm256_set1_ps(dataA[0 * cols + k]);
                __m256 in1 = _mm256_set1_ps(dataA[1 * cols + k]);
                __m256 in2 = _mm256_set1_ps(dataA[2 * cols + k]);
                __m256 in3 = _mm256_set1_ps(dataA[3 * cols + k]);
                __m256 in4 = _mm256_set1_ps(dataA[4 * cols + k]);
                __m256 in5 = _mm256_set1_ps(dataA[5 * cols + k]);
                __m256 in6 = _mm256_set1_ps(dataA[6 * cols + k]);
                __m256 in7 = _mm256_set1_ps(dataA[7 * cols + k]);

                __m256 ptrVar = _mm256_load_ps(ptr);

                out0 = _mm256_fmadd_ps(in0, ptrVar, out0);
                out1 = _mm256_fmadd_ps(in1, ptrVar, out1);
                out2 = _mm256_fmadd_ps(in2, ptrVar, out2);
                out3 = _mm256_fmadd_ps(in3, ptrVar, out3);
                out4 = _mm256_fmadd_ps(in4, ptrVar, out4);
                out5 = _mm256_fmadd_ps(in5, ptrVar, out5);
                out6 = _mm256_fmadd_ps(in6, ptrVar, out6);
                out7 = _mm256_fmadd_ps(in7, ptrVar, out7);

                ptr += 8;
            }
            _mm256_store_ps(dataOut + 0 * cols, out0);
            _mm256_store_ps(dataOut + 1 * cols, out1);
            _mm256_store_ps(dataOut + 2 * cols, out2);
            _mm256_store_ps(dataOut + 3 * cols, out3);
            _mm256_store_ps(dataOut + 4 * cols, out4);
            _mm256_store_ps(dataOut + 5 * cols, out5);
            _mm256_store_ps(dataOut + 6 * cols, out6);
            _mm256_store_ps(dataOut + 7 * cols, out7);
        };
        #pragma omp parallel for // num_threads(8)
        for (int j = 0; j < cols; j += 8)
        {
            getPackage(j, pack);
            for (int i = 0; i < rows; i += 8)
                calcPack(xData + i * temp, pack, data + i * cols + j);
        }
        free(pack);
    }
    counter.setEnd();
    return new Matrix(true, rows, cols, data);
}