
#include <opencv2/opencv.hpp>
#include <iostream>
#include "utils.hpp"
#include "config.hpp"
#include "detector.hpp"
#include "tracker.hpp"
#include "chronometer.hpp"
#include "drawer.hpp"


using namespace std;


int main(void)
{
    Config config;
    DetectionList detectionList;
    TrackingList trackingList(config);
    Drawer drawer(config);
    Chronometer chronometer;
    ObjectDetector detector(config);
    int trackingTag = 0;

    cv::VideoCapture cap(0); // open the default camera
    if(!cap.isOpened()) 
    {
        cout << "no capture device\n";
        exit(-1);
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, config.outputWindowWidth);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, config.outputWindowHeight);

    cv::Mat frame;
    cv::namedWindow("result",1);
    int frameNo = 0;
    
    for(chronometer.tic();;frameNo++)
    {
        cap >> frame; 
        detectionList.clearList();
        if (frameNo%5 == 0)
        {
            if(detector.detect(frame, detectionList))
            {
                trackingList.cleanTrackers();
                trackingList.removeFailedTrackers(detectionList);
                for(int i=0; i < detectionList.detectionLabels.size(); i++)
                {
                    int intersectionIndex = intersectionIndex = trackingList.checkIntersection(detectionList, i);
                    if (intersectionIndex == -1)
                        trackingList.initTracker(frame, detectionList, i, trackingTag);
                    else
                        trackingList.adjustTracker(frame, intersectionIndex, detectionList,  i);
                }
            }
        }
    trackingList.updateTrackers(frame);
    drawer.draw(frame, trackingList);
    cv::imshow("result", frame);
    if(cv::waitKey(30) >= 0) 
        break;
    
    }
    cap.release();
    cout << "FrameRate: " << (double)frameNo/(chronometer.toc()/1000) << endl;
    return 0;
}



// postprocess(Mat input, Mat outs)
// {
//     for (size_t i = 0; i < outs.size(); ++i) 
//     {
//     NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices); 
//     for (size_t i = 0; i < indices.size(); ++i)
//     {
//         int idx = indices[i];
//         Rect box = boxes[idx];
//         drawPred(classIds[idx], confidences[idx], box.x, box.y, box.x + box.width, box.y + box.height, frame); 
//     }
// }

