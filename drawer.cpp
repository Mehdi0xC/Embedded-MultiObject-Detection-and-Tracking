#include "utils.hpp"
#include <iostream>
#include <random>
#include "drawer.hpp"

Drawer::Drawer(Config& config)
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
    	cv::putText(frame, trackingList.trackingLabels[i], trackingList.trackingLabelPoints[i], font, fontSize, labelColor ,labelThickness);
    	rectangle(frame, trackingList.trackingRectangles[i], colorPlate[trackingList.trackingClasses[i]], boxThickness);
	}	
}


