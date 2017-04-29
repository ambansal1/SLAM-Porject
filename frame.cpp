#include "frame.h"

frame::frame() 
{
    Initialize();
}

void frame::Initialize()
{
    imagenames.resize(5);
    images.resize(5);
    imagenames[0] = "b1.JPG";
    imagenames[1] = "b2.JPG";
    imagenames[2] = "b3.JPG";
    imagenames[3] = "b4.JPG";
    imagenames[4] = "b5.JPG";
   
   length = images.size();

    for (int i=0;i<length;i++)
    {
        images[i] = imread(imagenames[i],1);
    }

    focal_length = 719.5459;
    maxSize = 1024;

    imsize = images[1].size();
    if (max(imsize.height,imsize.width) > maxSize)
    {
     double scale = maxSize/max(imsize.height,imsize.width);
     focal_length = scale*focal_length;
     Mat dummymat ;
     resize(images[1],dummymat,Size(), scale, scale, 3);
     imsize = dummymat.size();


    }

}


void frame::f2k ()
{
  
  K = Mat::zeros(3,3,CV_8UC1);
  K.diag(1);
  K.at<double>(1,1) = focal_length;
  K.at<double>(2,2) = focal_length;
}

