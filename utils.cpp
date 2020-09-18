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
        classes.clear();
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

void Drawer::draw(cv::Mat& frame, DetectionList& detectionList)
{
	for(int i=0; i < detectionList.detectionLabels.size(); i++)
	{
	   	// labelSize = cv::getTextSize(detectionList.detectionLabels[i], font, 0.5, 1,0);
	   	rectangle(frame, cv::Point(detectionList.labelPoints[i].x-5, detectionList.labelPoints[i].y-20), cv::Point(detectionList.labelPoints[i].x+240,detectionList.labelPoints[i].y+10), colorList.colorPlate[detectionList.classes[i]], -1);
    	cv::putText(frame, detectionList.detectionLabels[i], detectionList.labelPoints[i], font, fontSize, cv::Scalar(255,255,255),labelThickness);
    	rectangle(frame, detectionList.detectionRectangles[i], colorList.colorPlate[detectionList.classes[i]], boxThickness);
	}	
}


MultiTracker::MultiTracker(Config& config)
{
	trackerType = config.trackerType;
	nTrackers = 0;
}

cv::Ptr<cv::Tracker> MultiTracker::createTrackers()
{
	cv::Ptr<cv::Tracker> tracker;
	if (trackerType ==  "BOOSTING")
		tracker = cv::TrackerBoosting::create();
	else if (trackerType == "MIL")
		tracker = cv::TrackerMIL::create();
	else if (trackerType == "KFC")
		tracker = cv::TrackerKCF::create();
	else if (trackerType == "TLD")
		tracker = cv::TrackerTLD::create();
	else if (trackerType == "MEDIANFLOW")
		tracker = cv::TrackerMedianFlow::create();
	else if (trackerType == "GOTURN")
		tracker = cv::TrackerGOTURN::create();
	else if (trackerType == "MOSSE")
		tracker = cv::TrackerMOSSE::create();
	else if (trackerType == "CSRT")
		tracker = cv::TrackerCSRT::create();
	else {
    	std::cout << "Incorrect tracker name" << std::endl;
  }
  return tracker;
}


