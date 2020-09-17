#include "config.hpp"


Config::Config()
{
    // model = "faster_rcnn_inception_v2";
    // model = "faster_rcnn_resnet50";
    // model = "mask_rcnn_inception_v2";
    model = "ssd_mobilenet_v3";
    classes.push_back("person");
    indices.push_back(1);
    classes.push_back("bicycle");
    indices.push_back(2);
    classes.push_back("car");
    indices.push_back(3);
    classes.push_back("motorcycle");
    indices.push_back(4);
    classes.push_back("bus");
    indices.push_back(6);
    classes.push_back("truck");
    indices.push_back(8);    
    confidenceThreshold = 0.6;
}