
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
using namespace std;


// string CLASSES[] = {"background", "aeroplane", "bicycle", "bird", "boat",
//     "bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
//     "dog", "horse", "motorbike", "person", "pottedplant", "sheep",
//     "sofa", "train", "tvmonitor"};

string CLASSES[] = {"face", "person"};

// Mat postprocess(Mat outputMat, Mat inputMat);
int main(void)
{

    Config config;
    Chronometer chronometer;
    string modelConfiguration = "models/" + config.model +"/model_configurations.pbtxt";
    string modelWeights = "models/" + config.model +"/frozen_graph.pb";

    cout <<"Have openCL: " << boolalpha << ocl::haveOpenCL() << endl;
    if(ocl::haveOpenCL())
    {
        ocl::setUseOpenCL(true);
    }
    dnn::Net net = dnn::readNetFromTensorflow(modelWeights,modelConfiguration);

    if (net.empty())
    {
        std::cerr << "Can't load the network, sth went wrong" << std::endl;
        exit(-1);
    }

    net.setPreferableBackend(dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(dnn::DNN_TARGET_OPENCL);

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened()) 
    { // check if we succeeded
        cout << "no capture device :(\n";
        return -1;
    }


    cap.set(CAP_PROP_FRAME_WIDTH, 800);
	cap.set(CAP_PROP_FRAME_HEIGHT, 450);

    Mat frame;



    cv::namedWindow("result",1);
    double k = 0;
    chronometer.tic();
    for(;;k++)
    {
        Mat frame;   
        cap >> frame; 
        /////////////////////////////////////////
        // DO PROCESSING HERE
        /////////////////////////////////////////
        resize(frame, frame, Size(800,450));
        Mat inputBlob = dnn::blobFromImage(frame, 0.007843, Size(800,450), Scalar(127.5, 127.5, 127.5), false);
        net.setInput(inputBlob);

        Mat detection = net.forward("detection_out");
        Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

        ostringstream ss;
        float confidenceThreshold = 0.64;
        for (int i = 0; i < detectionMat.rows; i++)
        {
            float confidence = detectionMat.at<float>(i, 2);
            if (confidence > confidenceThreshold)
            {
                int idx = static_cast<int>(detectionMat.at<float>(i, 1));
                int xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
                int yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
                int xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
                int yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
                Rect object((int)xLeftBottom, (int)yLeftBottom,
                            (int)(xRightTop - xLeftBottom),
                            (int)(yRightTop - yLeftBottom));
                rectangle(frame, object, Scalar(0, 255, 0), 2);

                cout << CLASSES[idx] << ": " << confidence << endl;

                ss.str("");
                ss << confidence;
                String conf(ss.str());
                String label = CLASSES[idx] + ": " + conf;
                int baseLine = 0;
                Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
                putText(frame, label, Point(xLeftBottom, yLeftBottom),
                    FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));
                }
            }


        // vector<Mat> outs;
        // Mat detection = net.forward(outs, getOutputsNames(net));

        // postprocess(frame, outs);

        // Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

        /////////////////////////////////////////
        // END PROCESSING HERE
        /////////////////////////////////////////
        cv::imshow("result", frame);
        if(cv::waitKey(30) >= 0) break;
    }
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

