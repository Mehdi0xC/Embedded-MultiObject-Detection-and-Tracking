#ifndef DETECTOR_H_
#define DETECTOR_H_
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
class Detector
{
	private:
		std::string modelConfiguration;
	    std::string modelWeights;
	    cv::dnn::Net net;
    public:
    Detector(std::string);
    cv::Mat detect(cv::Mat, std::string*);
};

#endif
