#pragma once

#include "Layer.h"
#include "Pool.hpp"
#include "ReLU.h"
#include "Convolution.h"
#include "FullyConnection.h"

#include <vector>
#include <cstring>
#include <opencv2/opencv.hpp>

#define addStep push_back

using std::string;
using myCnn::Layer;

namespace myCnn
{
    using StepLayer = shared_ptr<Layer>;
    
    typedef struct OuterData
    {
    private:

        InnerData data;

    public:
        
        OuterData(const float* const data, const int& size);
        operator InnerData() const;
    
    }Data;

    typedef struct FileLoader_t
    {
    private:
    
        Matrix data;
    
    public:

        FileLoader_t(const string& filePath);
        operator Matrix() const;
    
    }FileLoader;

    enum
    {
        NONE, PART, ALL
    };

    class Process : public std::vector<StepLayer>
    {
    private:

        int logLevel = PART;

        Matrix currentResult;
        vector<int> convChannelDimensions;

        void printLog(const string& message, const int& log) const;

    public:

        Process() = default;

        ~Process() = default;

        void addSteps(const vector<StepLayer>& steps);
        void setChannelDimensions(const vector<int>& channelDimensions);
        void setLogLevel(const int& logLevel);
        void execute(const Matrix& input);
        Matrix getCurrentResult() const;

    };
}