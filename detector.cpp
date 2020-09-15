#include "detector.hpp"
#include <iostream>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

using namespace cv;
using namespace std;


Detector::Detector(std::string model, std::vector<std::string> detectionClasses)
{
    modelConfiguration = "models/" + model +"/model_configurations.pbtxt";
    modelWeights = "models/" + model +"/frozen_graph.pb";
    net = dnn::readNetFromTensorflow(modelWeights,modelConfiguration);
    classes = detectionClasses;
    if (net.empty())
    {
        std::cerr << "Can't load the network, sth went wrong" << std::endl;
        exit(-1);
    }


}


cv::Mat Detector::detect(cv::Mat frame)
{

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

                cout << classes[idx] << ": " << confidence << endl;

                ss.str("");
                ss << confidence;
                String conf(ss.str());
                String label =  classes[idx] + ": " + conf;
                int baseLine = 0;
                Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
                putText(frame, label, Point(xLeftBottom, yLeftBottom),
                    FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));
                }
            }
        return frame;
}