#include "SIFT_pair.h"

/*
SIFT_pair::SIFT_pair() 
{
    Initialize();
}

void SIFT_pair::Initialize()
{

}
*/
void SIFT_pair::match2viewSIFT(frame frames, int frame_1, int frame_2, bool visualize)
{

	//cv::Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	//SiftFeatureDetector detector;

	// load two images and depths
	Mat image_i = frames.images[frame_1];
	Mat image_j = frames.images[frame_2];

	int minHessian = 400;
	
	Ptr<SURF> detector = SURF::create(minHessian);
	//SiftFeatureDetector detector;


	vector<KeyPoint> keypoints_1, keypoints_2;

	// // detector.detect(frames.images[frame_1],keypoints_1);
	// // detector.detect(frames.images[frame_2],keypoints_2);
	// // SiftDescriptorExtractor extractor;
	Mat descriptor_1, descriptor_2;
	// // extractor.compute(frames.images[frame_1],keypoints_1,descriptor_1);
	// // extractor.compute(frames.images[frame_2],keypoints_2,descriptor_2);
	
	detector->detectAndCompute(frames.images[frame_1],Mat(),keypoints_1,descriptor_1);
	detector->detectAndCompute(frames.images[frame_2],Mat(),keypoints_2,descriptor_2);
	cout<<"length of keypoints 1 "<<keypoints_1.size()<<endl;
	cout<<"length of keypoints 2 "<<keypoints_2.size()<<endl;  
	cout<<"size of descriptor 1 "<<descriptor_1.size()<<endl;
	cout<<"size of descriptor 2 "<<descriptor_2.size()<<endl;


	
	//-- Step 2: Matching descriptor vectors using FLANN matcher
	FlannBasedMatcher matcher;
	std::vector< DMatch > matches;
	matcher.match( descriptor_1, descriptor_2, matches );

	cout<<"matches size"<<matches.size()<<endl;
	double max_dist = 0; double min_dist = 100;
	  //-- Quick calculation of max and min distances between keypoints
	for( int i = 0; i < descriptor_1.rows; i++ )
	{ double dist = matches[i].distance;
	    if( dist < min_dist ) min_dist = dist;
	    if( dist > max_dist ) max_dist = dist;
	}
	printf("-- Max dist : %f \n", max_dist );
	printf("-- Min dist : %f \n", min_dist );
	  //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
	  //-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
	  //-- small)
	  //-- PS.- radiusMatch can also be used here.


	std::vector< DMatch > good_matches;
	for( int i = 0; i < descriptor_1.rows; i++ )
	  { if( matches[i].distance <= max(2*min_dist, 0.08) )
	    { good_matches.push_back( matches[i]); }
	  }

	for( int i = 0; i < good_matches.size(); i++ )
	  { 
	  	int query_idx = good_matches[i].queryIdx;
	  	int train_idx = good_matches[i].trainIdx;
	  	pair_loc_1.push_back(keypoints_1[query_idx].pt);
	  	pair_loc_2.push_back(keypoints_2[train_idx].pt);
	  	// Point2f keypoint1_pt = keypoints_1[query_idx].pt;
	  	// Point2f keypoint2_pt = keypoints_2[train_idx].pt;
	  	// cout<<"point "<<i<<" coordinate: x: "<<keypoint1_pt.x<<" y: "<<keypoint1_pt.y<<endl;
	  	 //cout<<"point "<<i<<" coordinate: x: "<<keypoint2_pt.x<<" y: "<<keypoint2_pt.y<<endl;
	  }

	  //-- Draw only "good" matches

	if (visualize==true)
	{	Mat img_matches;
		drawMatches( frames.images[frame_1], keypoints_1, frames.images[frame_2], keypoints_2,
	               good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
	               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
	  //-- Show detected matches
		imshow( "Good Matches", img_matches );
		for( int i = 0; i < (int)good_matches.size(); i++ )
		{ printf( "-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx ); }
		waitKey(0);
	}


	// Mat img_keypoints;

	// cout<<"key point size"<<keypoints.size()<<endl;



	// drawKeypoints(frames.images[frame_1],keypoints,img_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	// cout<<"img_keypoints"<<img_keypoints.size()<<endl;
	// imshow("keypoints",img_keypoints);
	// waitKey(0);

}

void SIFT_pair::estimateE(double focal_length)
{
	//Point2d pp(0,0);
	//Mat mask;
	//OutputArray mask = noArray() ;
	//int method = RANSAC;
	E =  findFundamentalMat(pair_loc_1, pair_loc_2, FM_RANSAC, 3, 0.99);
//	cout<<"E matrix: "<<E<<endl;

}