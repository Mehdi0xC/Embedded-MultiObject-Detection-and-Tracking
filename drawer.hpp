#ifndef DRAWER_H
#define DRAWER_H

#include <chrono>
#include <opencv2/opencv.hpp>
#include <vector>
#include "config.hpp"
#include <opencv2/tracking.hpp>
#include "tracker.hpp"


class Drawer
{
    private:
         int font;
         cv::Scalar boxColor;
         cv::Scalar labelColor;
         float boxThickness;
         float labelThickness;
         float fontSize;
         std::vector<cv::Scalar> colorPlate;
    public:
        Drawer(Config&);
        void draw(cv::Mat& , TrackingList&);

};

#endif

