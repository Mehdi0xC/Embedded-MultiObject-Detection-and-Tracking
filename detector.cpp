#include "detector.hpp"
#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

using namespace cv;
using namespace std;


Detector::Detector(std::string model, std::vector<std::string> detectionClasses, std::vector<int> classIndices, float confidence)
{
    modelConfiguration = "models/" + model +"/model_configurations.pbtxt";
    modelWeights = "models/" + model +"/frozen_graph.pb";
    net = dnn::readNetFromTensorflow(modelWeights,modelConfiguration);
    classes = detectionClasses;
    confidenceThreshold = confidence;
    indices = classIndices;
    newDetection = false;
    if (net.empty())
    {
        std::cerr << "Can't load the network, sth went wrong" << std::endl;
        exit(-1);
    }
}


bool Detector::detect(cv::Mat frame, DetectionList& detectionList)
{

        newDetection = false;
		inputBlob = dnn::blobFromImage(frame, 0.007843, Size(320,320), Scalar(127.5, 127.5, 127.5), false);
        net.setInput(inputBlob);
        detection = net.forward("detection_out");
        Mat detectionOut(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
        for (int i = 0; i < detectionOut.rows; i++)
        {
            float confidence = detectionOut.at<float>(i, 2);
            int idx = static_cast<int>(detectionOut.at<float>(i, 1));
            it = std::find(indices.begin(), indices.end(), idx);
            if ((confidence > confidenceThreshold) && (it != indices.end()))
            {
                newDetection = true;
                idx = std::distance(indices.begin(), it);
                int xLeftBottom = static_cast<int>(detectionOut.at<float>(i, 3) * frame.cols);
                int yLeftBottom = static_cast<int>(detectionOut.at<float>(i, 4) * frame.rows);
                int xRightTop = static_cast<int>(detectionOut.at<float>(i, 5) * frame.cols);
                int yRightTop = static_cast<int>(detectionOut.at<float>(i, 6) * frame.rows);
                Rect object((int)xLeftBottom, (int)yLeftBottom,
                            (int)(xRightTop - xLeftBottom),
                            (int)(yRightTop - yLeftBottom));
                ostringstream ss;
                ss.str("");
                ss << (int)(confidence*100) << "%";
                String conf(ss.str());
                String label =  classes[idx] + ": " + conf;
                int baseLine = 0;
                detectionList.detectionRectangles.push_back(object);
                detectionList.confidence.push_back((int)confidence);
                detectionList.detectionLabels.push_back(label);
                detectionList.labelPoints.push_back(Point(xLeftBottom, yLeftBottom-10));
             }
        }   
        return newDetection;
}