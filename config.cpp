#include "config.hpp"

Config::Config()
{
	////////////////////////////////////////
	////////////////////////////////////////
	//		LABELS AND COLORS SETTINGS	  //			
	////////////////////////////////////////
	////////////////////////////////////////

	// Text colors for labels
	labelColor = cv::Scalar(250, 250, 250);

	// Font size of labels
	fontSize = 0.64;

	// Label font
	font = cv::FONT_HERSHEY_SIMPLEX;

	// Box Thickness
	boxThickness = 2;

	// Label Thickness
	labelThickness = 2;

	////////////////////////////////////////
	////////////////////////////////////////
	//			CAMERA SETTINGS			  //			
	////////////////////////////////////////
	////////////////////////////////////////

	// NOTE: COMMENT THESE AND CORRESPONDING LINES IN MAIN IF YOU'RE GONNA .....
	// ..... IMPLEMENT THE CODE ON RASPBERRY PI (OR IT WILL MESS UP CAMERA OUTPUT)
	
	// Output window width
	outputWindowWidth = 1000;

	// Output window height
	outputWindowHeight = 600;	

	////////////////////////////////////////
	////////////////////////////////////////
	//		ALGORITHMS SETTINGS			  //			
	////////////////////////////////////////
	////////////////////////////////////////

	// Model configuration address
	modelConfiguration = "models/ssd_mobilenet_v3/model_configurations.pbtxt";

	// Model weights address
	modelWeights = "models/ssd_mobilenet_v3/frozen_graph.pb";

	// Model input address
	modelSize = 320;

	// Specifies after how many frame processing iterations you want to call the model for prediction
	detectionRate = 5;

	////////////////////////////////////////
	////////////////////////////////////////
	//		ADJUSTABLE THRESHOLDS 		  //			
	////////////////////////////////////////
	////////////////////////////////////////

	// Controls the confidence threshold of the prediction model 
	confidenceThreshold = 0.5;

	// Controls the tracker re-identification mechanism
	intersectionThreshold = 0.5;

	// Controls the tracker merging mechanism 
	trackerMergeThreshold = 0.7;

	////////////////////////////////////////
	////////////////////////////////////////
	//	  DETECTION CLASSES SETTINGS 	  //			
	////////////////////////////////////////
	////////////////////////////////////////

	// NOTE: DONT CHANGE INDEX-CLASS CORRESPONDANCES OR YOULL PREDICT CAT FOR AN AIRPLANE

	// Person class detection index and color
	classes.push_back("person");
	indices.push_back(1);
	colors.push_back(cv::Scalar(0, 211, 255));

	// Bicycle class detection index and color
	classes.push_back("bicycle");
	indices.push_back(2);
	colors.push_back(cv::Scalar(255, 0, 255));

	// Car class detection index and color
	classes.push_back("car");
	indices.push_back(3);
	colors.push_back(cv::Scalar(0, 0, 255));

	// Motorcycle class detection index and color
	classes.push_back("motorcycle");
	indices.push_back(4);
	colors.push_back(cv::Scalar(255, 0, 255));

	// Bus class detection index and color
	classes.push_back("bus");
	indices.push_back(6);
	colors.push_back(cv::Scalar(255, 211, 0));

	// Truck class detection index and color
	classes.push_back("truck");
	indices.push_back(8);
	colors.push_back(cv::Scalar(0, 0, 255));

	// NOTE: YOU CAN ADD OTHER CLASSES OF COCO DATASET (UP TO 80 CLASSES)
}