#include "config.hpp"


Config::Config()
{
    // model = "faster_rcnn_inception_v2";
    // model = "faster_rcnn_resnet50";
    // model = "mask_rcnn_inception_v2";
    // boxColor = cv::Scalar(0,255,0);
    labelColor = cv::Scalar(250,250,250);
    fontSize = 0.64;
    outputWindowWidth = 1000;
    outputWindowHeight = 600;
    font = cv::FONT_HERSHEY_SIMPLEX;
    boxThickness = 2;
    labelThickness = 2;
	modelConfiguration = "models/ssd_mobilenet_v3/model_configurations.pbtxt";
    modelWeights = "models/ssd_mobilenet_v3/frozen_graph.pb";
	modelSize = 320;
    outputWindowWidth = 1000;
    outputWindowHeight = 600;   
    trackerType = "MOSSE";
    trackerMergeThreshold = 0.7;



    classes.push_back("person");
	indices.push_back(1);    
	colors.push_back(cv::Scalar(0,211,255));

    classes.push_back("bicycle");
    indices.push_back(2);
	colors.push_back(cv::Scalar(0,0,255));

    classes.push_back("car");
    indices.push_back(3);
 	colors.push_back(cv::Scalar(0,0,255));
   
    classes.push_back("motorcycle");
    indices.push_back(4);
 	colors.push_back(cv::Scalar(0,0,255));

    classes.push_back("bus");
    indices.push_back(6);
 	colors.push_back(cv::Scalar(0,0,255));

    classes.push_back("truck");
    indices.push_back(8);  
 	colors.push_back(cv::Scalar(0,0,255));
  
    confidenceThreshold = 0.6;
    intersectionThreshold = 0.2;
}