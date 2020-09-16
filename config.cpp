#include "config.hpp"


Config::Config()
{
    // model = "faster_rcnn_inception_v2";
    // model = "faster_rcnn_resnet50";
    // model = "mask_rcnn_inception_v2";
    model = "ssd_mobilenet_v3";
    classes.push_back("face");
    classes.push_back("person");
    confidenceThreshold = 0.6;
}