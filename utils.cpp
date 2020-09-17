#include "utils.hpp"
#include <iostream>
#include <chrono>



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
}


Drawer::Drawer(Config& config)
{
	font = config.font;
	boxColor = config.boxColor;
	labelColor = config.labelColor;
	boxThickness = config.boxThickness;
	labelThickness = config.labelThickness;

}

void Drawer::draw(cv::Mat& frame, DetectionList& detectionList)
{
	for(int i=0; i < detectionList.detectionLabels.size(); i++)
	{
	   	// labelSize = cv::getTextSize(detectionList.detectionLabels[i], font, 0.5, 1,0);
    	cv::putText(frame, detectionList.detectionLabels[i], detectionList.labelPoints[i], font, 1, labelColor,labelThickness);
    	rectangle(frame, detectionList.detectionRectangles[i], boxColor, boxThickness);
	}	
}


