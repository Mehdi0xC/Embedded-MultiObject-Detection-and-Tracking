
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
using namespace cv;
#include <iostream>
#include "utils.hpp"
#include "config.hpp"
#include "detector.hpp"
using namespace std;


int main(void)
{

    Config config;
    DetectionList currentDetectionList;
    DetectionList updatedDetectionList;

    Drawer drawer(config);
    Chronometer chronometer;
    Detector detector(config);
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened()) 
    {
        cout << "no capture device\n";
        exit(-1);
    }

    cap.set(CAP_PROP_FRAME_WIDTH, config.outputWindowWidth);
	cap.set(CAP_PROP_FRAME_HEIGHT, config.outputWindowHeight);

    Mat frame;
    cv::namedWindow("result",1);
    double frameNo = 0;
    chronometer.tic();
    for(;;frameNo++)
    {
        cap >> frame; 
        updatedDetectionList.clearList();
        if(detector.detect(frame, updatedDetectionList))
        {
            currentDetectionList = updatedDetectionList;
        }

        drawer.draw(frame, currentDetectionList);
        cv::imshow("result", frame);
        if(cv::waitKey(30) >= 0) break;
    }
    cap.release();
    cout << "FrameRate: " << frameNo/(chronometer.toc()/1000) << endl;
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

