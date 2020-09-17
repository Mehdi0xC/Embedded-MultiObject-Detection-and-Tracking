#include "utils.hpp"
#include <iostream>
#include <chrono>


Chronometer::Chronometer()
{
	// start = 0;
 //    end = 0;
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
}



Drawer::Drawer(int labelFont, cv::Scalar inputBoxColor, cv::Scalar inputLabelColor, float inputBoxThickness, float inputLabelThickness)
{
	font = labelFont;
	boxColor = inputBoxColor;
	labelColor = inputLabelColor;
	boxThickness = inputBoxThickness;
	labelThickness = inputLabelThickness;

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


