#include "tracker.hpp"
#include <iostream>

TrackingList::TrackingList(Config& config)
{
	intersectionThreshold = config.intersectionThreshold;
	trackerMergeThreshold = config.trackerMergeThreshold;
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

void TrackingList::cleanTrackers()
{
	int trackersToRemove = -1;
	for(int i = 0 ; i < trackers.size(); i++)
		for(int j = 0 ; j < trackers.size(); j++)
		{
			int maxIndex = 0;
			int minIndex = 0;
			if (i == j)
				continue;
			if (trackingRectangles[i].area() > trackingRectangles[j].area())
			{
				maxIndex = i;
				minIndex = j;
			}
			else
			{
				maxIndex = j;
				minIndex = i;
			}
			if((trackingRectangles[i] & trackingRectangles[j]).area() > trackerMergeThreshold*trackingRectangles[maxIndex].area())
			{
				trackersToRemove = maxIndex;
			}
		}
			
		if(trackersToRemove!=-1)	
			remove(trackersToRemove);
}

void TrackingList::removeFailedTrackers(DetectionList& detectionList)
{

	int trackersToRemove = -1;
	for(int i = 0 ; i < trackers.size(); i++)
		for(int j=0; j< detectionList.detectionLabels.size(); j++)
		{
			if((trackingRectangles[i] & detectionList.detectionRectangles[j]).area() != 0)
				continue;
			trackersToRemove = i;
		}


			
		if(trackersToRemove!=-1)	
			remove(trackersToRemove);
}


void TrackingList::adjustTracker(cv::Mat frame, int trackerIndex, DetectionList& detectionList, int detectionIndex)
{
	int tag = trackingTags[trackerIndex];
	std::string label = trackingLabels[trackerIndex];
	int trackingClass = trackingClasses[trackerIndex];
	
	remove(trackerIndex);  	

	cv::Ptr<cv::Tracker> tracker = cv::TrackerMOSSE::create();
    tracker->init(frame, detectionList.detectionRectangles[detectionIndex]);
    trackers.push_back(tracker);
    trackingTags.push_back(tag);
    trackingLabels.push_back(label);
    trackingRectangles.push_back(detectionList.detectionRectangles[detectionIndex]);
    trackingLabelPoints.push_back(detectionList.labelPoints[detectionIndex]);
    trackingClasses.push_back(trackingClass);  	
}

void TrackingList::remove(int trackerIndex)
{
	trackers.erase(trackers.begin() + trackerIndex);
	trackingTags.erase(trackingTags.begin() + trackerIndex);
    trackingLabels.erase(trackingLabels.begin() + trackerIndex);
    trackingRectangles.erase(trackingRectangles.begin() + trackerIndex);
    trackingLabelPoints.erase(trackingLabelPoints.begin() + trackerIndex);
    trackingClasses.erase(trackingClasses.begin() + trackerIndex);
}