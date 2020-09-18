#include "detector.hpp"
#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

using namespace std;
using namespace cv;

ObjectDetector::ObjectDetector(Config& config)
{

    newDetection = false;
    classes = config.classes;
    confidenceThreshold = config.confidenceThreshold;
    indices = config.indices;
    modelConfiguration = config.modelConfiguration;
    modelWeights = config.modelWeights;
    modelSize = config.modelSize;
    if(config.embedded)
        net = dnn::readNetFromCaffe(modelConfiguration, modelWeights);
    else
        net = dnn::readNetFromTensorflow(modelWeights,modelConfiguration);        
    if (net.empty())
    {
        std::cerr << "Can't load the network, sth went wrong" << std::endl;
        exit(-1);
    }
}


bool ObjectDetector::detect(cv::Mat frame)
{

        newDetection = false;
		inputBlob = dnn::blobFromImage(frame, 0.007843, Size(modelSize,modelSize), Scalar(127.5, 127.5, 127.5), false);
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
                Rect2d object((int)xLeftBottom, (int)yLeftBottom, (int)(xRightTop - xLeftBottom), (int)(yRightTop - yLeftBottom));
                ostringstream ss;
                ss.str("");
                ss << (int)(confidence*100) << "%";
                String conf(ss.str());
                String label =  classes[idx] + ": " + conf;
                int baseLine = 0;
                detectionClasses.push_back(idx);
                detectionRectangles.push_back(object);
                confidence.push_back((int)confidence);
                detectionLabels.push_back(label);
                labelPoints.push_back(Point(xLeftBottom+5, yLeftBottom-10));
             }
        }   
        return newDetection;
}


void ObjectDetector::clearList()
{
        detectionLabels.clear();
        detectionRectangles.clear();
        labelPoints.clear();
        confidence.clear();
        detectionClasses.clear();
} 