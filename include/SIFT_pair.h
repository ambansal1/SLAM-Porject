#ifndef SIFT_PAIR_H
#define SIFT_PAIR_H

#include <opencv2/calib3d/calib3d.hpp>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <frame.h>
#include <opencv2/features2d.hpp> 
//Thanks to Alessandro

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;



class SIFT_pair
{
public:
	Mat E;
	//Mat F;
	vector<Point2f> pair_loc_1;
	vector<Point2f> pair_loc_2;
	void Initialize();
	void match2viewSIFT(frame frames, int frame_1, int frame_2, bool visualize);
	void estimateE(double focal_length);
	//void estimateF();

	
};

#endif
