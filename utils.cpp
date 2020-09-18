#include "utils.hpp"
#include <iostream>

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
