
#include <opencv2/opencv.hpp>
#include <iostream>
#include "config.hpp"
#include "detector.hpp"
#include "tracker.hpp"
#include "chronometer.hpp"
#include "drawer.hpp"

using namespace std;

int main(void)
{

    ////////////////////////////////////////
    ////////////////////////////////////////
    //   INITIALIZE VARIABLES AND VECOTR  //
    ////////////////////////////////////////
    ////////////////////////////////////////

    TrackingList trackingList(config);
    Drawer drawer(config);
    Chronometer chronometer;
    ObjectDetector detector(config);
    int trackingID = 0;
    int detectionRate = config.detectionRate;
    cv::VideoCapture cap;
    if (config.captureFromVideo)
    {

        cap.open(config.videoAddress);
        if (!cap.isOpened())
        {
            cout << "no video provided, sth went wrong" << endl;
            exit(-1);
        }

    }
    else if (config.captureFromCamera)
    {
        cap.open(config.cameraDevice);
        if (!cap.isOpened())
        {
            cout << "no capture device, sth went wrong" << endl;
            exit(-1);
        }
        cap.set(cv::CAP_PROP_FRAME_WIDTH, config.outputWindowWidth);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, config.outputWindowHeight);
    }
    else
    {
        cout << "no input specified" << endl;
        exit(-1);
    }

    cv::Mat frame;
    cv::namedWindow("result", 1);
    int frameNo = 0;

    ////////////////////////////////////////
    ////////////////////////////////////////
    //              MAIN LOOP             //
    ////////////////////////////////////////
    ////////////////////////////////////////

    for (chronometer.tic();; frameNo++)
    {
        cap >> frame;
        detector.clearList();
        if (frameNo % detectionRate == 0)
        {

            bool newDetection = detector.detect(frame);
            trackingList.cleanTrackers();
            trackingList.removeFailedTrackers(detector);
            if (newDetection)
            {
                for (int i = 0; i < detector.detectionLabels.size(); i++)
                {
                    int intersectionIndex = trackingList.checkIntersection(detector, i);
                    if (intersectionIndex == -1)
                        trackingList.initTracker(frame, detector, i, trackingID);
                    else
                        trackingList.adjustTracker(frame, intersectionIndex, detector,  i);
                }
            }
        }
        trackingList.updateTrackers(frame);
        drawer.draw(frame, trackingList);
        cv::imshow("result", frame);
        if (cv::waitKey(30) >= 0)
            break;

    }

    ////////////////////////////////////////
    ////////////////////////////////////////
    //           END OF MAIN LOOP         //
    ////////////////////////////////////////
    ////////////////////////////////////////

    cap.release();
    cout << "FrameRate: " << (double)frameNo / (chronometer.toc() / 1000) << endl;
    return 0;

    ////////////////////////////////////////
    ////////////////////////////////////////
    //           END OF program           //
    ////////////////////////////////////////
    ////////////////////////////////////////

}


