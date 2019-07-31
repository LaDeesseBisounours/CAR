#include "opencv2/opencv.hpp"
#include <iostream>
 
using namespace std;
using namespace cv;
 
int main(){
 
  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name


    // /home/chat/car/vision_cars_clip2.mp4

  VideoCapture cap("/home/chat/car/vision_cars_clip2.mp4"); 
    
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
     
  while(1){
 
    Mat frame;
    // Capture frame-by-frame
    cap >> frame;
    Mat hsvFrame;
    Mat RedMask1, YellowMask1, RedMask2;
    Mat res(frame.size(), frame.type());
    res.setTo(0);

  
    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    cvtColor(frame, hsvFrame, COLOR_BGR2HSV);
 
    inRange(hsvFrame, Scalar(0, 140, 70), Scalar(10, 255, 255), RedMask1);
    inRange(hsvFrame, Scalar(175, 140, 70), Scalar(180, 255, 255), RedMask2);
    inRange(hsvFrame, Scalar(25, 140, 70), Scalar(45, 255, 255), YellowMask1);
    // Display the resulting frame
    res.setTo(Scalar(0, 0, 255), RedMask1 + RedMask2);
    res.setTo(Scalar(150,250,0), YellowMask1);
    imshow( "Frame", res);
 
    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
  
  // When everything done, release the video capture object
  cap.release();
 
  // Closes all the frames
  destroyAllWindows();
     
  return 0;
}
