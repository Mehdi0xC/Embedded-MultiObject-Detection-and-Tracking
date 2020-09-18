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

TrackingList::TrackingList()
{

}

void TrackingList::clearList()
{
		trackers.clear();
	    trackingLabels.clear();
        trackingRectangles.clear();
        trackingLabelPoints.clear();
        trackingClasses.clear();
}



ColorList::ColorList(Config& config)
{

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0,180); // guaranteed unbiased

	auto random_integer = uni(rng);

	int step = (int)(255/config.indices.size());
  	for(int i=0; i < config.indices.size(); i++)
    	colorPlate.push_back(cv::Scalar(uni(rng),uni(rng),uni(rng))); 
}


Drawer::Drawer(Config& config):colorList(config)
{
	font = config.font;
	boxColor = config.boxColor;
	labelColor = config.labelColor;
	boxThickness = config.boxThickness;
	labelThickness = config.labelThickness;
	fontSize = config.fontSize;
	// this->colorList = ColorList(config);

}

void Drawer::draw(cv::Mat& frame, TrackingList& trackingList)
{
	for(int i=0; i < trackingList.trackers.size(); i++)
	{
	   	rectangle(frame, cv::Point(trackingList.trackingLabelPoints[i].x-5, trackingList.trackingLabelPoints[i].y-20), cv::Point(trackingList.trackingLabelPoints[i].x+240,trackingList.trackingLabelPoints[i].y+10), colorList.colorPlate[trackingList.trackingClasses[i]], -1);
    	cv::putText(frame, trackingList.trackingLabels[i], trackingList.trackingLabelPoints[i], font, fontSize, cv::Scalar(255,255,255),labelThickness);
    	rectangle(frame, trackingList.trackingRectangles[i], colorList.colorPlate[trackingList.trackingClasses[i]], boxThickness);
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


