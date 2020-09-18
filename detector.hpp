#ifndef DETECTOR_H_
#define DETECTOR_H_
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <vector>
#include "utils.hpp"
#include "config.hpp"

class ObjectDetector
{
	private:
		std::string modelConfiguration;
	    std::string modelWeights;
	    cv::dnn::Net net;
	    float confidenceThreshold;
    	std::vector<int>::iterator it;
    	std::vector<int> indices;
    	bool newDetection;
    	cv::Mat inputBlob;
    	cv::Mat detection; 
    	int modelSize;


    public:
        ObjectDetector(Config&);
        bool detect(cv::Mat);
        std::vector<std::string> classes;
        std::vector<std::string> detectionLabels;
        std::vector<cv::Rect2d> detectionRectangles;
        std::vector<cv::Point> labelPoints;
        std::vector<int> confidence;
        std::vector<int> detectionClasses;
        void clearList();


};

#endif
