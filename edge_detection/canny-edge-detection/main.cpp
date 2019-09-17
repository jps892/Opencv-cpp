#include <iostream>
#include "gray.hpp"
#include "threshold.hpp"
#include "nonmaxsupp.hpp"
#include "filter.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

int main(int argc, char **argv)
{
    cout << "canny edge detection "<<argv[1] << endl;

    cv::Mat img = cv::imread(argv[1]);
    cv::Mat gray_img = gray(img);
    cv::Mat filter_img;
    cv::Mat angles = filter(gray_img, filter_img);
    cv::Mat nms_img = nonmaxsupp(filter_img, angles);
    cv::Mat canny = threshold(nms_img, 20, 40);

    cv::imshow("canny", canny);
    cv::waitKey(0);

    return 0;
}
