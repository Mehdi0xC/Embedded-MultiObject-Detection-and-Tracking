#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <opencv2/opencv.hpp>
#include <vector>
class Chronometer
{
	private:
		typedef std::chrono::high_resolution_clock Clock;
    	typedef std::chrono::milliseconds milliseconds;
    	Clock::time_point start;
    	Clock::time_point end;
    	milliseconds elapsed;

    public:
        Chronometer();
        void tic();
        int toc();
};


class DetectionList
{
    private:

    public:
        DetectionList();
        std::vector<std::string> detectionLabels;
        std::vector<cv::Rect> detectionRectangles;
        std::vector<cv::Point> labelPoints;
        std::vector<int> confidence;
        void clearList();
};

class Drawer
{
    private:
         cv::Size labelSize;
         int font;
         cv::Scalar boxColor;
         cv::Scalar labelColor;
         float boxThickness;
         float labelThickness;

    public:
        Drawer(int, cv::Scalar, cv::Scalar, float, float);
        void draw(cv::Mat& , DetectionList&);

};
#endif

