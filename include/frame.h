#ifndef FRAME_H
#define FRAME_H

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
class frame
{
public:
	std::vector<string> imagenames;
	vector<cv::Mat> images;
 
	int length ;
	double focal_length;
	frame();
	void Initialize();
	int maxSize;
	Size imsize ;
	Mat K ;
	void f2k ();
	
};

#endif
