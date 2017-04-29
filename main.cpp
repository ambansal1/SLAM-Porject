#include <frame.h>
#include <SIFT_pair.h>


int main()
{ 
	bool visualize = true;
	frame frames;
	frames.f2k();
	SIFT_pair pairs;
	pairs.match2viewSIFT(frames,0,1,visualize);
	namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", frames.images[0]);
    waitKey(0);
    cout<<frames.imsize<<endl;
    return 0;
	
}