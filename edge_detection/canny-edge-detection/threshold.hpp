#ifndef __threshold__hpp__
#define __threshold__hpp__
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

cv::Mat threshold(cv::Mat imgin,int low, int high);
#endif
