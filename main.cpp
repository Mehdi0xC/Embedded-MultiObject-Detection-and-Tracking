
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/trace.hpp>
#include <opencv2/core/ocl.hpp>
using namespace cv;
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "utils.hpp"
#include "config.hpp"
#include "detector.hpp"
using namespace std;


// Mat postprocess(Mat outputMat, Mat inputMat);
int main(void)
{

    Config config;
    DetectionList currentDetectionList;
    DetectionList updatedDetectionList;

    Drawer drawer(config);
    // Chronometer chronometer;
    Detector detector(config);
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened()) 
    {
        cout << "no capture device\n";
        exit(-1);
    }

 //    cap.set(CAP_PROP_FRAME_WIDTH, 1000);
	// cap.set(CAP_PROP_FRAME_HEIGHT, 600);

    Mat frame;
    cv::namedWindow("result",1);
    // double frameNo = 0;
    // chronometer.tic();
    for(;;)
    {
        cap >> frame; 
        /////////////////////////////////////////
        // DO PROCESSING HERE
        /////////////////////////////////////////
        // resize(frame, frame, Size(100,75));
        updatedDetectionList.clearList();
        if(detector.detect(frame, updatedDetectionList))
        {
            currentDetectionList = updatedDetectionList;
        }
        // vector<Mat> outs;
        // Mat detection = net.forward(outs, getOutputsNames(net));

        // postprocess(frame, outs);

        // Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

        /////////////////////////////////////////
        // END PROCESSING HERE
        /////////////////////////////////////////
        drawer.draw(frame, currentDetectionList);
        cv::imshow("result", frame);
        // frame.release();
        if(cv::waitKey(30) >= 0) break;
    }
    // cout << "Elapsed time: " <<  chronometer.toc() << endl;
    // cout << "FrameRate: " << k/(ms.count()/1000) << endl;
    return 0;
}



// postprocess(Mat input, Mat outs)
// {
//     for (size_t i = 0; i < outs.size(); ++i) 
//     {

//         float* data = (float*)outs[i].data;
//         for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) {
//             Mat scores = outs[i].row(j).colRange(5, outs[i].cols); 
//             Point classIdPoint;
//             double confidence;
//             minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
//             if (confidence > confThreshold)
//             {
//                 int centerX = (int)(data[0] * frame.cols); 
//                 int centerY = (int)(data[1] * frame.rows); 
//                 int width = (int)(data[2] * frame.cols); 
//                 int height = (int)(data[3] * frame.rows);
//                 int left = centerX - width / 2;
//                 int top = centerY - height / 2;

//                 classIds.push_back(classIdPoint.x);
//                 confidences.push_back((float)confidence);
//                 boxes.push_back(Rect(left, top, width, height));
//             }
//         }
//     }

//     vector<int> indices;
//     NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices); 
//     for (size_t i = 0; i < indices.size(); ++i)
//     {
//         int idx = indices[i];
//         Rect box = boxes[idx];
//         drawPred(classIds[idx], confidences[idx], box.x, box.y, box.x + box.width, box.y + box.height, frame); 
//     }
// }

