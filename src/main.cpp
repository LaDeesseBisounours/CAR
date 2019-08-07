#include"opencv2/opencv.hpp"
#include<iostream>
#include<tuple>
#include<queue>
#include<vector>
 
using namespace std;
using namespace cv;
typedef tuple<int,int> position;
typedef tuple<position, unsigned> pos_n;
typedef queue<position> q_pos;
typedef vector<tuple<position,unsigned>> vec_pos_n;

#define MAGIC_VAL 54

pos_n
findBlock(Mat src, unsigned i, unsigned j) {
    q_pos v;
    int tmpi = i;
    int tmpj = j;
    v.push(make_tuple(tmpi, tmpj));
    unsigned counter = 0;
    unsigned low_vert;
    unsigned low_hor;
    unsigned high_vert;
    unsigned high_hor;
    while (!v.empty()) {
        auto current = v.front();
        for (int x = -1; x < 2; x += 2) {
            for (int y = -1; y < 2; y += 2) {
                int x1 = x + get<0>(current);
                int y1 = y + get<1>(current);
                if (x1 < 0 || y1 < 0 || y1 >= src.cols || x1 >= src.rows)
                    continue;
                if (src.at<uchar>(x1, y1) != 0
                        && src.at<uchar>(x1, y1) != MAGIC_VAL) {
                    if (x1 < low_hor)
                        low_hor = x1;
                    if (x1 > high_hor)
                        high_hor = x1;
                    if (y1 < low_vert)
                        low_vert = y1;
                    if (y1 > high_vert)
                        high_vert = y1;
                    counter++;
                    v.push(make_tuple(x1, y1));
                    src.at<uchar>(x1, y1) = MAGIC_VAL;
                }
            }
        }
        v.pop();
    }
    return make_tuple(make_tuple((low_hor + high_hor) / 2,
                (low_vert + high_vert) / 2), counter);
}
 
int
main(){
 
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
    Mat RedMask1, YellowMask, RedMask2;
    Mat res(frame.size(), frame.type());
    res.setTo(0);

  
    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    cvtColor(frame, hsvFrame, COLOR_BGR2HSV);
 
    inRange(hsvFrame, Scalar(0, 140, 70), Scalar(10, 255, 255), RedMask1);
    inRange(hsvFrame, Scalar(175, 140, 70), Scalar(180, 255, 255), RedMask2);
    inRange(hsvFrame, Scalar(25, 140, 70), Scalar(45, 255, 255), YellowMask);
    
    unsigned count = 0;
    uchar curr;
    RedMask1 += RedMask2;
    vec_pos_n YBlocks();
    vec_pos_n RBlocks();

    //tuple position x, y and number pixels

    for (int i = 0; i < YellowMask.rows; i++) {
        for (int j = 0; j < YellowMask.cols; j++) {
            if ((curr = YellowMask.at<uchar>(i,j)) != 0) {
                pos_n block = findBlock(YellowMask, i, j);

            }
            if ((curr = RedMask1.at<uchar>(i,j)) != 0) {
            }
        }
    }
    cout << "num pic : " << count << " value " << (uint8_t)curr << endl;

    // Display the resulting frame
    res.setTo(Scalar(0, 0, 255), RedMask1);
    res.setTo(Scalar(150,250,0), YellowMask);
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
