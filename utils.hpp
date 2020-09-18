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
        std::vector<int> detectionClasses;
        void clearList();
};

class TrackingList
{
    private:

    public:
        TrackingList();
        std::vector<cv::Ptr<cv::Tracker>> trackers;
        std::vector<std::string> trackingLabels;
        std::vector<cv::Rect2d> trackingRectangles;
        std::vector<cv::Point> trackingLabelPoints;
        std::vector<int> trackingClasses;        
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
        void draw(cv::Mat& , TrackingList&);

};

// class MultiTrackerMaker
// {
//     private:
//         std::string trackerType;
//         int nTrackers;

//     public:
//         MultiTrackerMaker(Config&);
//         cv::Ptr<cv::Tracker> createTracker();
// ;
// };


#endif

