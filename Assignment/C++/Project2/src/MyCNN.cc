#include "MyCNN.h"
#include <cmath>
#include <ostream>

using cv::Mat;
using myCnn::Matrix;

myCnn::OuterData::OuterData(const float* const data, const int& size)
{
    float* result = new float[size];

    memcpy(result, data, size * sizeof(float));

    this->data = InnerData(result, myCnn::Deleter());
}

myCnn::OuterData::operator myCnn::InnerData() const
{
    return this->data;
}

myCnn::FileLoader_t::FileLoader_t(const string& filePath)
{
    using cv::ImreadModes;
    using std::min;

    Mat image = cv::imread(filePath, ImreadModes::IMREAD_COLOR);
    
    if (image.empty() == true)
        throw "Open File Failed.";

    vector<Mat> planes;
    cv::split(image, planes);

    const int channels = image.channels();
    const int size = min(planes[0].cols, planes[0].rows);
    this->data = Matrix({1, channels}, size);

    for (int t = 0, dim; t < channels; ++t)
        for (int x = 0; x < size; ++x)
            for (int y = 0; y < size; ++y)
            {
                dim = channels - t - 1;
                this->data({0, t}, x, y) = static_cast<float>(planes[dim].at<uchar>(x, y) / 255.0F);
            }
}

myCnn::FileLoader_t::operator Matrix() const
{
    return this->data;
}

void myCnn::Process::printLog(const string& message, const int& log) const
{
    if (log > this->logLevel)
        return;
        
    std::cout << message << std::endl;
}

void myCnn::Process::addSteps(const vector<StepLayer>& steps)
{
    this->insert(this->end(), steps.begin(), steps.end());
}

void myCnn::Process::setChannelDimensions(const vector<int>& channelDimensions)
{
    this->convChannelDimensions = channelDimensions;
}

void myCnn::Process::setLogLevel(const int& logLevel)
{
    if (logLevel < NONE || logLevel > ALL)
        throw "Illegal Log Level Value.";

    this->logLevel = logLevel;
}

void myCnn::Process::execute(const Matrix& input)
{
    if (this->size() == 0)
    {
        this->printLog("No Layer in Queue.", PART);
        return;
    }

    size_t counter = 0, channelCounter = 0;

    try
    {
        while (counter < this->size())
        {
            StepLayer currentLayer = this->operator[](counter);

            if (currentLayer->getType() == myCnn::LayerType::CONV)
            {
                if (channelCounter < this->convChannelDimensions.size())
                    dynamic_cast<Convolution*>(currentLayer.get())->setChannelDimension(this->convChannelDimensions[channelCounter++]);
                else
                    throw "No Enough Channel Arguments for All Convolution Layers.";
            }

            if (counter == 0)
                currentLayer->execute(input);
            else
                currentLayer->execute(this->currentResult);

            this->currentResult = currentLayer->getResult();
            
            if (currentLayer->getType() == myCnn::LayerType::CONV)
                this->currentResult.redimension();

            if (this->logLevel == ALL)
            {
                std::cout << "Layer \033[33mNo." << counter + 1 << "\033[0m, Info:" << std::endl;
                currentLayer->display();
                std::cout << std::endl;
                
                std::cout << "Layer \033[33mNo." << counter + 1 << "\033[0m, Result:" << std::endl;
                this->currentResult.display();
                std::cout << std::endl;
            }

            ++counter;
        }
    }
    catch (const char* error)
    {
        char str[256];
        sprintf(str, "Layer No.%ld Error: ", counter);
        
        this->printLog(string(str) + error, NONE);
        return;
    }

    this->printLog("Process Successfully.", PART);
}

Matrix myCnn::Process::getCurrentResult() const
{
    return this->currentResult.clone();
}