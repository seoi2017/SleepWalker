#include "Matrix.h"

myMath::Matrix::Matrix(const bool &isAligned, const int &rows, const int &cols, const bool &isConstant) : aligned(isAligned), rows(rows), cols(cols)
{
    if (isAligned == true)
        posix_memalign((void**)&this->data , MEM_ALIGN, rows * cols * sizeof(float));
    else
        this->data = new float[rows * cols];
    if (isConstant == false)
        srand(static_cast<float>(time(0)));
    for (register int i = 0, j = rows * cols; i < j; ++i)
        this->data[i] = isConstant == true ? 1.0 : static_cast<float>(rand() % 100000 - 50000) / 10000;
}

myMath::Matrix::Matrix(const bool &align, const int &a, const int &b, float* &c) : aligned(align), rows(a), cols(b), data(c)
{
    // TODO : Check the align.
}

myMath::Matrix::~Matrix()
{
    delete this->data;
}

bool myMath::Matrix::getAligned() const
{
    return this->aligned;
}

int myMath::Matrix::getCol() const
{
    return this->cols;
}

int myMath::Matrix::getRow() const
{
    return this->rows;
}

float* myMath::Matrix::getData() const
{
    return this->data;
}

void myMath::Matrix::print()
{
    for (register int i = 0, j = this->rows * this->cols; i < j; ++i)
    {
        cout << this->data[i] << " ";
        if ((i + 1) % this->cols == 0)
            cout << endl;
    }
}

myMath::Matrix* myMath::Matrix::getTranspose() const
{
    float *newData = nullptr;
    if (this->aligned == true)
        posix_memalign((void**)&newData , MEM_ALIGN, this->rows * this->cols * sizeof(float));
    else
        newData = new float[this->rows * this->cols];
    // TODO : could be spped up by AVX or OpenMP methods
    int newRows = this->cols, newCols = this->rows;
    for (register int i = 0; i < newRows; ++i)
        for (register int j = 0; j < newCols; ++j)
            newData[i * newCols + j] = this->data[j * newRows + i];
    return new Matrix(this->aligned, this->cols, this->rows, newData);
}

myMath::Timer::Timer()
{
    this->start = system_clock::now();
    this->end = this->start;
}

void myMath::Timer::setStart()
{
    this->start = system_clock::now();
}

void myMath::Timer::setEnd()
{
    this->end = system_clock::now();
}

double myMath::Timer::getTimeInterval(const myMath::TimeType &type) const
{
    union
    {
        milliseconds timeMilli;
        microseconds timeMicro;
        nanoseconds timeNano;
    }duration;
    switch (type)
    {
    case SEC:
        duration.timeMilli = duration_cast<milliseconds>(this->end - this->start);
        return duration.timeMilli.count() / static_cast<double>(1000);
    case MSEC:
        duration.timeMicro = duration_cast<microseconds>(this->end - this->start);
        return duration.timeMicro.count() / static_cast<double>(1000);
    case USEC:
        duration.timeNano = duration_cast<nanoseconds>(this->end - this->start);
        return duration.timeNano.count() / static_cast<double>(1000);
    default:
        throw "Invalid Time Type";
    }
}

myMath::Matrix* myMath::multiMethodVanilla(const Matrix &x, const Matrix &y, Timer &counter)
{
    // Illegal Checking
    if (x.getAligned() == true || y.getAligned() == true)
        throw "The matrix should NOT be aligned";
    if (x.getCol() != y.getRow())
        throw "Invalid Argument Matrices";
    int rows = x.getRow(), cols = y.getCol(), temp = x.getCol();
    // Variables Definition
    float *data = nullptr, *xData = x.getData(), *yData = y.getData();
    data = new float[rows * cols];
    // Working Block
    counter.setStart();
    {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                for (int k = 0; k < temp; ++k)
                    data[i * cols + j] += xData[i * temp + k] * yData[k * cols + j];
    }
    counter.setEnd();
    return new Matrix(false, rows, cols, data);
}

myMath::Matrix* myMath::multiMethodOpenBLAS(const Matrix &x, const Matrix &y, Timer &counter)
{
    // Illegal Checking
    if ((x.getAligned() ^ y.getAligned()) == true)
        throw "The two matrix need to be all aligned or none aligned";
    if (x.getCol() != y.getRow())
        throw "Invalid Argument Matrices";
    int rows = x.getRow(), cols = y.getCol(), temp = x.getCol();
    // Variables Definition
    float *data = nullptr, *xData = x.getData(), *yData = y.getData();
    posix_memalign((void**)&data , MEM_ALIGN, rows * cols * sizeof(float));
    // Working Block
    counter.setStart();
    {
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, rows, cols, temp, 1.0, xData, temp, yData, temp, 0.0, data, cols);
    }
    counter.setEnd();
    return new Matrix(true, rows, cols, data);
}

myMath::Matrix* myMath::multiMethodAdvanced(const Matrix &x, const Matrix &y, Timer &counter)
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
    float *data = nullptr, *xData = x.getData(), *yData = y.getData();
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