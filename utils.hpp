#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <opencv2/opencv.hpp>
#include <vector>
#include "config.hpp"
#include <opencv2/tracking.hpp>

class Chronometer
{
	private:
		typedef std::chrono::high_resolution_clock Clock;
    	typedef std::chrono::milliseconds milliseconds;
    	Clock::time_point start;
    	Clock::time_point end;
    	milliseconds elapsed;

    public:
        Chronometer();
        void tic();
        int toc();
};


class DetectionList
{
    private:

    public:
        DetectionList();
        std::vector<std::string> detectionLabels;
        std::vector<cv::Rect2d> detectionRectangles;
        std::vector<cv::Point> labelPoints;
        std::vector<int> confidence;
        std::vector<int> classes;
        void clearList();
};

class ColorList
{
    private:
    public:
        ColorList(Config&);
        std::vector<cv::Scalar> colorPlate;
};


class Drawer
{
    private:
         int font;
         cv::Scalar boxColor;
         cv::Scalar labelColor;
         float boxThickness;
         float labelThickness;
         float fontSize;
         ColorList colorList;
    public:
        Drawer(Config&);
        void draw(cv::Mat& , DetectionList&);

};

class MultiTracker
{
    private:
        std::string trackerType;
        int nTrackers;

    public:
        MultiTracker(Config&);
        cv::Ptr<cv::Tracker> createTrackers();
;
};


#endif

