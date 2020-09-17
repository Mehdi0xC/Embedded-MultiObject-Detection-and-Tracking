#ifndef DETECTOR_H_
#define DETECTOR_H_
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <vector>
class Detector
{
	private:
		std::string modelConfiguration;
	    std::string modelWeights;
	    cv::dnn::Net net;
	    float confidenceThreshold;
    	std::vector<int>::iterator it;
    	std::vector<int> indices;

    public:
    Detector(std::string, std::vector<std::string>, std::vector<int>, float);
    cv::Mat detect(cv::Mat);
    std::vector<std::string> classes;

};

#endif
