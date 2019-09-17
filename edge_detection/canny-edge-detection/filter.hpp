#ifndef __filter__hpp__
#define __filter__hpp__
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

cv::Mat filter(cv::Mat input, cv::Mat &angle);
vector<vector<double> > createFilter(int row, int column, double sigmaIn);
cv::Mat useFilter(cv::Mat img_in, vector<vector<double> > filterIn);

#endif
