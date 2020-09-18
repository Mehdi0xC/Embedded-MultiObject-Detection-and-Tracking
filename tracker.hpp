#ifndef TRACKER_H_
#define TRACKER_H_
#include "utils.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/tracking.hpp>

class TrackingList
{
    private:
        float trackerMergeThreshold;
    public:
        TrackingList(Config&);
        std::vector<cv::Ptr<cv::Tracker>> trackers;
        std::vector<std::string> trackingLabels;
        std::vector<cv::Rect2d> trackingRectangles;
        std::vector<cv::Point> trackingLabelPoints;
        std::vector<int> trackingClasses;  
        std::vector<int> trackingTags;
        void removeFailedTrackers(DetectionList&);
        float intersectionThreshold;      
        void clearList();
        void initTracker(cv::Mat, DetectionList&, int, int&);
        int checkIntersection(DetectionList&, int);
        void adjustTracker(cv::Mat, int, DetectionList&, int);
        void cleanTrackers();
        void remove(int);


};
#endif
