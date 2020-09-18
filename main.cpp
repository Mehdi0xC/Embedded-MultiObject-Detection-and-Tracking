
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/tracking.hpp>

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

    // cv::Ptr<cv::Tracker> tracker;
    // tracker = cv::TrackerKCF::create();
    // tracker = cv::TrackerMOSSE::create();

    Config config;
    DetectionList detectionList;
    TrackingList trackingList(config);
    // MultiTrackerMaker multiTrackerMaker(config);
    Drawer drawer(config);
    Chronometer chronometer;
    ObjectDetector detector(config);
    // cv::Ptr<cv::MultiTracker> multiTracker = cv::MultiTracker::create();
    int trackingTag = 1;
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
    int id = 0;
    chronometer.tic();
    for(;;frameNo++)
    {
        cap >> frame; 
        detectionList.clearList();
        if (frameNo%5 == 0)
        if(detector.detect(frame, detectionList))
        {
        
        trackingList.cleanTrackers();
        trackingList.removeFailedTrackers(detectionList);

        for(int i=0; i < detectionList.detectionLabels.size(); i++)
        {
            int intersectionIndex = -1;
            // if(trackingList.trackers.size()==0)
            // {
            //     trackingList.initTracker(frame, detectionList, i, trackingTag);
            // }
            // else
            // {
            intersectionIndex = trackingList.checkIntersection(detectionList, i);
            if (intersectionIndex == -1)
            {             
                trackingList.initTracker(frame, detectionList, i, trackingTag);
                trackingTag++;
            }
            else
            {
                trackingList.adjustTracker(frame, intersectionIndex, detectionList,  i);
            }
            // }

        }
                    // multiTracker->add(multiTrackerMaker.createTracker(), frame, detectionList.detectionRectangles[i]); 
            // else
            // { 
            // for(int i=0; i < detectionList.detectionLabels.size(); i++)
            //     for(int j=0; j < trackingList.detectionLabels.size(); j++)
            //     {
            //         if((detectionList.detectionRectangles[i] & trackingList.detectionRectangles[j]).area()<(0.5*(detectionList.detectionRectangles[i].area()+trackerList.detectionRectangles[j].area())))
            //             multiTracker->add(multiTrackerMaker.createTracker(), frame, detectionList.detectionRectangles[i]);  
            //         else
            //     }
            // }
        }

        for(int j=0; j < trackingList.trackers.size(); j++)
        {
            if(trackingList.trackers[j]->update(frame, trackingList.trackingRectangles[j]))
            {
                    // trackingList.trackingLabels[j]
                    // trackingList.trackingRectangles[j]
                    trackingList.trackingLabelPoints[j].x = trackingList.trackingRectangles[j].x+5;
                    trackingList.trackingLabelPoints[j].y = trackingList.trackingRectangles[j].y-10;
            }

        }

        // multiTracker->update(frame);

          // Draw tracked objects
          // for(unsigned i=0; i<multiTracker->getObjects().size(); i++)
          // {
          //   rectangle(frame, multiTracker->getObjects()[i], cv::Scalar(255,255,255), 2, 1);
          //   // multiTracker->getObjects()[i].x 
          // }

        // // cv::Rect2d rr(currentDetectionList.detectionRectangles[0]);
        // bool ok = tracker->update(frame, currentDetectionList.detectionRectangles[0]);

        // // if(ok)
        // //     rectangle(frame, currentDetectionList.detectionRectangles[0], cv::Scalar( 255, 0, 0 ), 2, 1 );


        drawer.draw(frame, trackingList);
        cv::imshow("result", frame);
        if(cv::waitKey(30) >= 0) break;
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

