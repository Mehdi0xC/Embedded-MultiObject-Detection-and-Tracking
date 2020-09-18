#ifndef CONFIG_H_
#define CONFIG_H_
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

class Config
{
public:
    Config();
    std::string modelConfiguration;
    std::string modelWeights;
    std::vector<cv::Scalar> colors;
    std::vector<std::string> classes;
    std::vector<int> indices;
    float intersectionThreshold;
    float trackerMergeThreshold;
    float confidenceThreshold;
    int font;
    cv::Scalar boxColor;
    cv::Scalar labelColor;
    float boxThickness;
    float labelThickness;
    int outputWindowWidth;
    int outputWindowHeight;
    float fontSize;
    bool embedded;
    int modelSize;
    std::string trackerType;


};

#endif
