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

myMath::Matrix *myMath::methodBruteForce2D(const Matrix &x, const Matrix &y, Timer &counter)
{
    // Illegal Checking
    if (x.getCol() != y.getRow())
        throw "Invalid Argument Matrices";
    // Variables Definition
    int rows = x.getRow(), cols = y.getCol(), temp = x.getCol();
    float **data = new float*[rows], **xData = new float*[x.getRow()], **yData = new float*[y.getRow()];
    for (int i = 0; i < rows; ++i)
        data[i] = new float[cols];
    // Data Format Conversion
    for (int i = 0; i < x.getRow(); ++i)
    {
        xData[i] = new float[x.getCol()];
        for (int j = 0; j < x.getCol(); ++j)
            xData[i][j] = x.getData()[i * x.getCol() + j];
    }
    for (int i = 0; i < y.getRow(); ++i)
    {
        yData[i] = new float[y.getCol()];
        for (int j = 0; j < y.getCol(); ++j)
            yData[i][j] = y.getData()[i * y.getCol() + j];
    }
    // Working Block
    counter.setStart();
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                for (int k = 0; k < temp; k++)
                    data[i][j] += xData[i][k] * yData[k][j];
    }
    counter.setEnd();
    float *fData = new float[rows * cols];
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            fData[i * cols + j] = data[i][j];
    delete[] data;
    delete[] xData;
    delete[] yData;
    return new Matrix(true, rows, cols, fData);
}

myMath::Matrix *myMath::methodBruteForce1D(const Matrix &x, const Matrix &y, Timer &counter)
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
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                for (int k = 0; k < temp; k++)
                    data[i * cols + j] += xData[i * temp + k] * yData[k * cols + j];
    }
    counter.setEnd();
    return new Matrix(true, rows, cols, data);
}

myMath::Matrix *myMath::methodRSITranspose(const Matrix &x, const Matrix &y, Timer &counter)
{
    // Illegal Checking
    if (x.getCol() != y.getRow())
        throw "Invalid Argument Matrices";
    // Variables Definition
    Matrix *ty = y.getTranspose();
    int rows = x.getRow(), cols = y.getCol(), temp = x.getCol();
    float **data = new float*[rows], **xData = new float*[x.getRow()], **yData = new float*[ty->getRow()];
    for (int i = 0; i < rows; ++i)
        data[i] = new float[cols];
    // Data Format Conversion
    for (int i = 0; i < x.getRow(); ++i)
    {
        xData[i] = new float[x.getCol()];
        for (int j = 0; j < x.getCol(); ++j)
            xData[i][j] = x.getData()[i * x.getCol() + j];
    }
    for (int i = 0; i < ty->getRow(); ++i)
    {
        yData[i] = new float[ty->getCol()];
        for (int j = 0; j < ty->getCol(); ++j)
            yData[i][j] = ty->getData()[i * ty->getCol() + j];
    }
    // Working Block
    counter.setStart();
    {
        for (register int i = 0; i < rows; ++i)
            for (register int j = 0; j < cols; ++j)
            {
                float &target = data[i][j];
                for (register int k = 0; k < temp; ++k)
                    target += xData[i][k] * yData[j][k];
            }
    }
    counter.setEnd();
    float *fData = new float[rows * cols];
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            fData[i * cols + j] = data[i][j];
    delete[] data;
    delete[] xData;
    delete[] yData;
    delete ty;
    return new Matrix(true, rows, cols, fData);
}

myMath::Matrix *myMath::methodRSI_IKJ(const Matrix &x, const Matrix &y, Timer &counter)
{
    // Illegal Checking
    if (x.getCol() != y.getRow())
        throw "Invalid Argument Matrices";
    // Variables Definition
    int rows = x.getRow(), cols = y.getCol(), temp = x.getCol();
    float **data = new float*[rows], **xData = new float*[x.getRow()], **yData = new float*[y.getRow()];
    for (int i = 0; i < rows; ++i)
        data[i] = new float[cols];
    // Data Format Conversion
    for (int i = 0; i < x.getRow(); ++i)
    {
        xData[i] = new float[x.getCol()];
        for (int j = 0; j < x.getCol(); ++j)
            xData[i][j] = x.getData()[i * x.getCol() + j];
    }
    for (int i = 0; i < y.getRow(); ++i)
    {
        yData[i] = new float[y.getCol()];
        for (int j = 0; j < y.getCol(); ++j)
            yData[i][j] = y.getData()[i * y.getCol() + j];
    }
    // Working Block
    counter.setStart();
    {
        for (register int i = 0; i < rows; ++i)
            for (register int k = 0; k < temp; ++k)
            {
                register float inner = xData[i][k];
                for (register int j = 0; j < cols; ++j)
                    data[i][j] += inner * yData[k][j];
            }
    }
    counter.setEnd();
    float *fData = new float[rows * cols];
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            fData[i * cols + j] = data[i][j];
    delete[] data;
    delete[] xData;
    delete[] yData;
    return new Matrix(true, rows, cols, fData);
}

myMath::Matrix *myMath::methodRSI_IKJ_1D(const Matrix &x, const Matrix &y, Timer &counter)
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

myMath::Matrix *myMath::methodLoopUnrolling(const Matrix &x, const Matrix &y, Timer &counter)
{
    // Illegal Checking
    if (x.getCol() != y.getRow())
        throw "Invalid Argument Matrices";
    if (y.getCol() % 8 != 0)
        throw "Matrices' size must be divisible by 8";
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
                for (register int j = 0, jPtr = k * cols; j < cols; j += 8)
                {
                    data[iPtr1 + j + 0] += inner * yData[jPtr + j + 0];
                    data[iPtr1 + j + 1] += inner * yData[jPtr + j + 1];
                    data[iPtr1 + j + 2] += inner * yData[jPtr + j + 2];
                    data[iPtr1 + j + 3] += inner * yData[jPtr + j + 3];
                    data[iPtr1 + j + 4] += inner * yData[jPtr + j + 4];
                    data[iPtr1 + j + 5] += inner * yData[jPtr + j + 5];
                    data[iPtr1 + j + 6] += inner * yData[jPtr + j + 6];
                    data[iPtr1 + j + 7] += inner * yData[jPtr + j + 7];
                }
            }
    }
    counter.setEnd();
    return new Matrix(true, rows, cols, data);
}

myMath::Matrix *myMath::methodSSE(const Matrix &x, const Matrix &y, Timer &counter)
{
    // Illegal Checking
    if (x.getCol() != y.getRow())
        throw "Invalid Argument Matrices";
    if (y.getCol() % 4 != 0 || x.getRow() % 4 != 0 || x.getCol() % 4 != 0)
        throw "Matrices' size must be divisible by 4";
    // Variables Definition
    int rows = x.getRow(), cols = y.getCol(), temp = x.getCol();
    float *data = new float[rows * cols], *xData = x.getData(), *yData = y.getData();
    // Working Block
    counter.setStart();
    {
        __m128 left = _mm_setzero_ps();
        __m128 right = _mm_setzero_ps();
        __m128 target = _mm_setzero_ps();
        for (register int i = 0, iPtr1 = 0, iPtr2 = 0; i < rows; ++i, iPtr1 += cols, iPtr2 += temp)
            for (register int k = 0; k < temp; ++k)
            {
                left = _mm_load1_ps(xData + (iPtr2 + k));
                for (register int j = 0, jPtr = k * cols; j < cols; j += 4)
                {
                    target = _mm_loadu_ps(data + (iPtr1 + j));
                    right = _mm_loadu_ps(yData + (jPtr + j));
                    _mm_storeu_ps(data + (iPtr1 + j), _mm_fmadd_ps(left, right, target));
                }
            }
    }
    counter.setEnd();
    return new Matrix(true, rows, cols, data);
}

myMath::Matrix *myMath::methodAVX(const Matrix &x, const Matrix &y, Timer &counter)
{
    // Illegal Checking
    if (x.getCol() != y.getRow())
        throw "Invalid Argument Matrices";
    if (y.getCol() % 8 != 0 || x.getRow() % 8 != 0 || x.getCol() % 8 != 0)
        throw "Matrices' size must be divisible by 8";
    // Variables Definition
    int rows = x.getRow(), cols = y.getCol(), temp = x.getCol();
    float *data = new float[rows * cols], *xData = x.getData(), *yData = y.getData();
    // Working Block
    counter.setStart();
    {
        __m256 left = _mm256_setzero_ps();
        __m256 right = _mm256_setzero_ps();
        __m256 target = _mm256_setzero_ps();
        for (register int i = 0, iPtr1 = 0, iPtr2 = 0; i < rows; ++i, iPtr1 += cols, iPtr2 += temp)
            for (register int k = 0; k < temp; ++k)
            {
                left = _mm256_set1_ps(xData[iPtr2 + k]);
                for (register int j = 0, jPtr = k * cols; j < cols; j += 8)
                {
                    target = _mm256_loadu_ps(data + (iPtr1 + j));
                    right = _mm256_loadu_ps(yData + (jPtr + j));
                    _mm256_storeu_ps(data + (iPtr1 + j), _mm256_fmadd_ps(left, right, target));
                }
            }
    }
    counter.setEnd();
    return new Matrix(true, rows, cols, data);
}

myMath::Matrix *myMath::methodAVXAlignment(const Matrix &x, const Matrix &y, Timer &counter)
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
        __m256 left = _mm256_setzero_ps();
        __m256 right = _mm256_setzero_ps();
        __m256 target = _mm256_setzero_ps();
        for (register int i = 0, iPtr1 = 0, iPtr2 = 0; i < rows; ++i, iPtr1 += cols, iPtr2 += temp)
            for (register int k = 0; k < temp; ++k)
            {
                left = _mm256_set1_ps(xData[iPtr2 + k]);
                for (register int j = 0, jPtr = k * cols; j < cols; j += 8)
                {
                    target = _mm256_load_ps(data + (iPtr1 + j));
                    right = _mm256_load_ps(yData + (jPtr + j));
                    _mm256_store_ps(data + (iPtr1 + j), _mm256_fmadd_ps(left, right, target));
                }
            }
    }
    counter.setEnd();
    return new Matrix(true, rows, cols, data);
}

myMath::Matrix *myMath::methodAVXAlignmentPacked(const Matrix &x, const Matrix &y, Timer &counter)
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
        for (register int i = 0, iPtr1 = 0, iPtr2 = 0; i < rows; ++i, iPtr1 += cols, iPtr2 += temp)
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
    counter.setEnd();
    return new Matrix(true, rows, cols, data);
}

myMath::Matrix *myMath::methodAVXAPOpenMP(const Matrix &x, const Matrix &y, Timer &counter)
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