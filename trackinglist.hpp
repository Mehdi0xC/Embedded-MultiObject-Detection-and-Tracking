#ifndef TRACKINGLIST_H_
#define TRACKINGLIST_H_
#include "objectdetector.hpp"
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
    void removeFailedTrackers(ObjectDetector&);
    float intersectionThreshold;
    void clearList();
    void initTracker(cv::Mat, ObjectDetector&, int, int&);
    int checkIntersection(ObjectDetector&, int);
    void adjustTracker(cv::Mat, int, ObjectDetector&, int);
    void cleanTrackers();
    void remove(int);
    std::string trackerType;
    void updateTrackers(cv::Mat);


};
#endif
