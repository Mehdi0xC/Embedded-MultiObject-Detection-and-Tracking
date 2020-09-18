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
        TrackingList(Config&);
        std::vector<cv::Ptr<cv::Tracker>> trackers;
        std::vector<std::string> trackingLabels;
        std::vector<cv::Rect2d> trackingRectangles;
        std::vector<cv::Point> trackingLabelPoints;
        std::vector<int> trackingClasses;  
        std::vector<int> trackingTags;
        float intersectionThreshold;      
        void clearList();
        void initTracker(cv::Mat, DetectionList&, int, int&);
        int checkIntersection(DetectionList&, int);
        void adjustTracker(cv::Mat, int, DetectionList&, int);

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
         std::vectoor<cv::Scalar> colorPlate;
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

