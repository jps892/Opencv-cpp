#ifndef __nonmaxsupp__hpp__
#define __nonmaxsupp__hpp__
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

cv::Mat nonmaxsupp(cv::Mat input, cv::Mat angle);

#endif
