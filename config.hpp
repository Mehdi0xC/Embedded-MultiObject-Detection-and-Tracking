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
    
    std::vector<std::string> classes;
    std::vector<int> indices;

    float confidenceThreshold;
    int font;
    cv::Scalar boxColor;
    cv::Scalar labelColor;
    float boxThickness;
	float labelThickness;
};

#endif
