#include "utils.hpp"
#include <iostream>
#include <chrono>
#include <random>



Chronometer::Chronometer()
{

}

void Chronometer::tic()
{
	start = Clock::now();
}
int Chronometer::toc()
{
	end = Clock::now();
	elapsed = std::chrono::duration_cast<milliseconds>(end - start);
	return elapsed.count();
}

DetectionList::DetectionList()
{

}

void DetectionList::clearList()
{
	    detectionLabels.clear();
        detectionRectangles.clear();
        labelPoints.clear();
        confidence.clear();
        detectionClasses.clear();
}

TrackingList::TrackingList(Config& config)
{
	intersectionThreshold = config.intersectionThreshold;
}

void TrackingList::clearList()
{
		trackers.clear();
	    trackingLabels.clear();
        trackingRectangles.clear();
        trackingLabelPoints.clear();
        trackingClasses.clear();
        trackingTags.clear();
}

void TrackingList::initTracker(cv::Mat frame, DetectionList& detectionList, int i, int& trackingTag)
{
        cv::Ptr<cv::Tracker> tracker = cv::TrackerMOSSE::create();
        tracker->init(frame, detectionList.detectionRectangles[i]);
        trackers.push_back(tracker);
        trackingTags.push_back(trackingTag);
        trackingLabels.push_back(detectionList.detectionLabels[i] + " ID: #" + std::to_string(trackingTag));
        trackingRectangles.push_back(detectionList.detectionRectangles[i]);
        trackingLabelPoints.push_back(detectionList.labelPoints[i]);
        trackingClasses.push_back(detectionList.detectionClasses[i]);  
        trackingTag++;
}


int TrackingList::checkIntersection(DetectionList& detectionList, int i)
{
	for(int j = 0; j< trackers.size(); j++)
		if(
			(detectionList.detectionRectangles[i] & trackingRectangles[j]).area()>(intersectionThreshold*trackingRectangles[j].area())
			||
			(detectionList.detectionRectangles[i] & trackingRectangles[j]).area()>(intersectionThreshold*detectionList.detectionRectangles[j].area())			
			)
			return j;
	return -1;
}

void TrackingList::adjustTracker(cv::Mat frame, int trackerIndex, DetectionList& detectionList, int detectionIndex)
{
	int tag = trackingTags[trackerIndex];
	std::string label = trackingLabels[trackerIndex];
	int trackingClass = trackingClasses[trackerIndex];
	trackers.erase(trackers.begin() + trackerIndex);
	cv::Ptr<cv::Tracker> tracker = cv::TrackerMOSSE::create();
    tracker->init(frame, detectionList.detectionRectangles[detectionIndex]);
    trackers.push_back(tracker);
    trackingTags.push_back(tag);
    trackingLabels.push_back(label);
    trackingRectangles.push_back(detectionList.detectionRectangles[detectionIndex]);
    trackingLabelPoints.push_back(detectionList.labelPoints[detectionIndex]);
    trackingClasses.push_back(trackingClass);  	
}


Drawer::Drawer(Config& config):colorList(config)
{
	font = config.font;
	boxColor = config.boxColor;
	labelColor = config.labelColor;
	boxThickness = config.boxThickness;
	labelThickness = config.labelThickness;
	fontSize = config.fontSize;
	colorPlate = config.colors;
	// this->colorList = ColorList(config);

}

void Drawer::draw(cv::Mat& frame, TrackingList& trackingList)
{
	for(int i=0; i < trackingList.trackers.size(); i++)
	{
	   	rectangle(frame, cv::Point(trackingList.trackingLabelPoints[i].x-5, trackingList.trackingLabelPoints[i].y-20), cv::Point(trackingList.trackingLabelPoints[i].x+240,trackingList.trackingLabelPoints[i].y+10), colorPlate[trackingList.trackingClasses[i]], -1);
    	cv::putText(frame, trackingList.trackingLabels[i], trackingList.trackingLabelPoints[i], font, fontSize, cv::Scalar(255,255,255),labelThickness);
    	rectangle(frame, trackingList.trackingRectangles[i], colorPlate[trackingList.trackingClasses[i]], boxThickness);
	}	
}


// MultiTrackerMaker::MultiTrackerMaker(Config& config)
// {
// 	trackerType = config.trackerType;
// 	nTrackers = 0;
// }

// cv::Ptr<cv::Tracker> MultiTrackerMaker::createTracker()
// {
// 	cv::Ptr<cv::Tracker> tracker;
// 	if (trackerType ==  "BOOSTING")
// 		tracker = cv::TrackerBoosting::create();
// 	else if (trackerType == "MIL")
// 		tracker = cv::TrackerMIL::create();
// 	else if (trackerType == "KFC")
// 		tracker = cv::TrackerKCF::create();
// 	else if (trackerType == "TLD")
// 		tracker = cv::TrackerTLD::create();
// 	else if (trackerType == "MEDIANFLOW")
// 		tracker = cv::TrackerMedianFlow::create();
// 	else if (trackerType == "GOTURN")
// 		tracker = cv::TrackerGOTURN::create();
// 	else if (trackerType == "MOSSE")
// 		tracker = cv::TrackerMOSSE::create();
// 	else if (trackerType == "CSRT")
// 		tracker = cv::TrackerCSRT::create();
// 	else {
//     	std::cout << "Incorrect tracker name" << std::endl;
//   }
//   return tracker;
// }


