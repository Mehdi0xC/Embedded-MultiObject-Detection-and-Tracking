#include "tracker.hpp"
#include <iostream>

TrackingList::TrackingList(Config& config)
{
	intersectionThreshold = config.intersectionThreshold;
	trackerMergeThreshold = config.trackerMergeThreshold;
	trackerType = config.trackerType;
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

void TrackingList::initTracker(cv::Mat frame, ObjectDetector& objectDetector, int i, int& trackingTag)
{
	cv::Ptr<cv::Tracker> tracker;
	if (trackerType == "MOSSE")
		tracker = cv::TrackerMOSSE::create();
	else
		tracker = cv::TrackerKCF::create();
	tracker->init(frame, objectDetector.detectionRectangles[i]);
	trackers.push_back(tracker);
	trackingTags.push_back(trackingTag);
	trackingLabels.push_back(objectDetector.detectionLabels[i] + " ID: #" + std::to_string(trackingTag));
	trackingRectangles.push_back(objectDetector.detectionRectangles[i]);
	trackingLabelPoints.push_back(objectDetector.labelPoints[i]);
	trackingClasses.push_back(objectDetector.detectionClasses[i]);
	trackingTag++;
}


int TrackingList::checkIntersection(ObjectDetector& objectDetector, int i)
{
	for (int j = 0; j < trackers.size(); j++)
		if (
		    (objectDetector.detectionRectangles[i] & trackingRectangles[j]).area() > (intersectionThreshold * trackingRectangles[j].area())
		    ||
		    (objectDetector.detectionRectangles[i] & trackingRectangles[j]).area() > (intersectionThreshold * objectDetector.detectionRectangles[j].area())
		)
			return j;
	return -1;
}

void TrackingList::cleanTrackers()
{
	int trackersToRemove = -1;
	for (int i = 0 ; i < trackers.size(); i++)
		for (int j = 0 ; j < trackers.size(); j++)
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
			if ((trackingRectangles[i] & trackingRectangles[j]).area() > trackerMergeThreshold * trackingRectangles[maxIndex].area())
			{
				trackersToRemove = maxIndex;
			}
		}

	if (trackersToRemove != -1)
		remove(trackersToRemove);
}

void TrackingList::removeFailedTrackers(ObjectDetector& objectDetector)
{
	int trackersToRemove = -1;
	for (int i = 0 ; i < trackers.size(); i++)
		for (int j = 0; j < objectDetector.detectionLabels.size(); j++)
		{
			if ((trackingRectangles[i] & objectDetector.detectionRectangles[j]).area() != 0)
				continue;
			trackersToRemove = i;
		}
	if (trackersToRemove != -1)
		remove(trackersToRemove);
}


void TrackingList::adjustTracker(cv::Mat frame, int trackerIndex, ObjectDetector& objectDetector, int detectionIndex)
{
	int tag = trackingTags[trackerIndex];
	std::string label = trackingLabels[trackerIndex];
	int trackingClass = trackingClasses[trackerIndex];

	remove(trackerIndex);

	cv::Ptr<cv::Tracker> tracker = cv::TrackerMOSSE::create();
	tracker->init(frame, objectDetector.detectionRectangles[detectionIndex]);
	trackers.push_back(tracker);
	trackingTags.push_back(tag);
	trackingLabels.push_back(label);
	trackingRectangles.push_back(objectDetector.detectionRectangles[detectionIndex]);
	trackingLabelPoints.push_back(objectDetector.labelPoints[detectionIndex]);
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


void TrackingList::updateTrackers(cv::Mat frame)
{
	for (int i = 0; i < trackers.size(); i++)
	{
		if (trackers[i]->update(frame, trackingRectangles[i]))
		{
			// trackingList.trackingLabels[j]
			// trackingList.trackingRectangles[j]
			trackingLabelPoints[i].x = trackingRectangles[i].x + 5;
			trackingLabelPoints[i].y = trackingRectangles[i].y - 10;
		}

	}
}

