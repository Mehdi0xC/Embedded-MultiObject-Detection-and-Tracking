
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


// string CLASSES[] = {"background", "aeroplane", "bicycle", "bird", "boat",
//     "bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
//     "dog", "horse", "motorbike", "person", "pottedplant", "sheep",
//     "sofa", "train", "tvmonitor"};

// Mat postprocess(Mat outputMat, Mat inputMat);
int main(void)
{

    Config config;
    Chronometer chronometer;
    Detector detector(config.model);

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened()) 
    {
        cout << "no capture device\n";
        exit(-1);
    }

    cap.set(CAP_PROP_FRAME_WIDTH, 800);
	cap.set(CAP_PROP_FRAME_HEIGHT, 450);

    Mat frame;
    cout << config.classes[1];
    // cv::namedWindow("result",1);

    // double frameNo = 0;

    // chronometer.tic();
    // for(;;frameNo++)
    // {
    //     Mat frame;   
    //     cap >> frame; 
    //     /////////////////////////////////////////
    //     // DO PROCESSING HERE
    //     /////////////////////////////////////////
    //     resize(frame, frame, Size(800,450));
    //     frame = detector.detect(frame, &config.classes);
        
    //     // vector<Mat> outs;
    //     // Mat detection = net.forward(outs, getOutputsNames(net));

    //     // postprocess(frame, outs);

    //     // Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

    //     /////////////////////////////////////////
    //     // END PROCESSING HERE
    //     /////////////////////////////////////////
    //     cv::imshow("result", frame);
    //     if(cv::waitKey(30) >= 0) break;
    // }
    cout << "Elapsed time: " <<  chronometer.toc() << endl;
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

