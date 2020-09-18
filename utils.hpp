#ifndef UTILS_H
#define UTILS_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "config.hpp"


class DetectionList
{
    private:

    public:
        DetectionList();
        std::vector<std::string> detectionLabels;
        std::vector<cv::Rect2d> detectionRectangles;
        std::vector<cv::Point> labelPoints;
        std::vector<int> confidence;
        std::vector<int> detectionClasses;
        void clearList();
};


#endif

