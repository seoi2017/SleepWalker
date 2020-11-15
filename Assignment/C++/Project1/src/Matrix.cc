#include "Matrix.h"

myMath::Matrix::Matrix(const bool &isAligned, const int &rows, const int &cols, const bool &isConstant) : aligned(isAligned), rows(rows), cols(cols)
{
    if (isAligned == true)
        posix_memalign((void **)&this->data, MEM_ALIGN, rows * cols * sizeof(float));
    else
        this->data = new float[rows * cols];
    if (isConstant == false)
        srand(static_cast<float>(time(0)));
    for (register int i = 0, j = rows * cols; i < j; ++i)
        this->data[i] = isConstant == true ? 1.0 : static_cast<float>(rand() % 100000 - 50000) / 10000;
}

myMath::Matrix::Matrix(const bool &align, const int &a, const int &b, float *&c) : aligned(align), rows(a), cols(b), data(c)
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

float *myMath::Matrix::getData() const
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

myMath::Matrix *myMath::Matrix::getTranspose() const
{
    float *newData = nullptr;
    if (this->aligned == true)
        posix_memalign((void **)&newData, MEM_ALIGN, this->rows * this->cols * sizeof(float));
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
    } duration;
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

myMath::Matrix *myMath::multiMethodBasic(const Matrix &x, const Matrix &y, Timer &counter)
{
    // Illegal Checking
    if (x.getCol() != y.getRow())
        throw "Invalid Argument Matrices";
    // Variables Definition
    int rows = x.getRow(), cols = y.getCol(), temp = x.getCol();
    float *data = new float[rows * cols], *xData = x.getData(), *yData = y.getData();
    // Working Block
    counter.setStart();
    {
        for (register int i = 0, iPtr1 = 0, iPtr2 = 0; i < rows; ++i, iPtr1 += cols, iPtr2 += temp)
            for (register int k = 0; k < temp; ++k)
            {
                register float inner = xData[iPtr2 + k];
                for (register int j = 0, jPtr = k * cols; j < cols; ++j)
                    data[iPtr1 + j] += inner * yData[jPtr + j];
            }
    }
    counter.setEnd();
    return new Matrix(true, rows, cols, data);
}

myMath::Matrix *myMath::multiMethodOpenBLAS(const Matrix &x, const Matrix &y, Timer &counter)
{
    // Illegal Checking
    if ((x.getAligned() ^ y.getAligned()) == true)
        throw "The two matrix need to be all aligned or none aligned";
    if (x.getCol() != y.getRow())
        throw "Invalid Argument Matrices";
    int rows = x.getRow(), cols = y.getCol(), temp = x.getCol();
    // Variables Definition
    float *data = nullptr, *xData = x.getData(), *yData = y.getData();
    posix_memalign((void **)&data, MEM_ALIGN, rows * cols * sizeof(float));
    // Working Block
    counter.setStart();
    {
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, rows, cols, temp, 1.0, xData, temp, yData, temp, 0.0, data, cols);
    }
    counter.setEnd();
    return new Matrix(true, rows, cols, data);
}

myMath::Matrix *myMath::multiMethodAdvanced(const Matrix &x, const Matrix &y, Timer &counter)
{
    // Illegal Checking
    if (x.getAligned() == false || y.getAligned() == false)
        throw "The matrix should be aligned";
    if (x.getCol() != y.getRow())
        throw "Invalid Argument Matrices";
    if (y.getCol() % 8 != 0 || x.getRow() % 8 != 0 || x.getCol() % 8 != 0)
        throw "Matrices' size must be divisible by 8";
    // Variables Definition
    int rows = x.getRow(), cols = y.getCol(), temp = x.getCol();
    float *data = nullptr, *xData = x.getData(), *yData = y.getData();
    posix_memalign((void **)&data, MEM_ALIGN, rows * cols * sizeof(float));
    // Working Block
    counter.setStart();
    {
        #pragma omp parallel for
        for (int i = 0; i < rows; ++i)
        {
            register int iPtr1 = i * cols, iPtr2 = i * temp;
            __m256 left0 = _mm256_setzero_ps();
            __m256 left1 = _mm256_setzero_ps();
            __m256 left2 = _mm256_setzero_ps();
            __m256 left3 = _mm256_setzero_ps();
            __m256 left4 = _mm256_setzero_ps();
            __m256 left5 = _mm256_setzero_ps();
            __m256 left6 = _mm256_setzero_ps();
            __m256 left7 = _mm256_setzero_ps();

            __m256 right = _mm256_setzero_ps();
            __m256 target = _mm256_setzero_ps();
            for (register int k = 0; k < temp; k += 8)
            {
                left0 = _mm256_broadcast_ss(xData + iPtr2 + k + 0);
                left1 = _mm256_broadcast_ss(xData + iPtr2 + k + 1);
                left2 = _mm256_broadcast_ss(xData + iPtr2 + k + 2);
                left3 = _mm256_broadcast_ss(xData + iPtr2 + k + 3);
                left4 = _mm256_broadcast_ss(xData + iPtr2 + k + 4);
                left5 = _mm256_broadcast_ss(xData + iPtr2 + k + 5);
                left6 = _mm256_broadcast_ss(xData + iPtr2 + k + 6);
                left7 = _mm256_broadcast_ss(xData + iPtr2 + k + 7);
                for (register int j = 0, jPtr = k * cols; j < cols; j += 8)
                {
                    target = _mm256_load_ps(data + (iPtr1 + j));
                    right = _mm256_load_ps(yData + (jPtr + j));
                    target = _mm256_fmadd_ps(left0, right, target);
                    target = _mm256_fmadd_ps(left1, right, target);
                    target = _mm256_fmadd_ps(left2, right, target);
                    target = _mm256_fmadd_ps(left3, right, target);
                    target = _mm256_fmadd_ps(left4, right, target);
                    target = _mm256_fmadd_ps(left5, right, target);
                    target = _mm256_fmadd_ps(left6, right, target);
                    target = _mm256_fmadd_ps(left7, right, target);
                    _mm256_store_ps(data + (iPtr1 + j), target);
                }
            }
        }
    }
    counter.setEnd();
    return new Matrix(true, rows, cols, data);
}