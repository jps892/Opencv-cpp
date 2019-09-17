#include "gray.hpp"
using namespace std;
using namespace cv;

cv::Mat gray(cv::Mat img)
{
    cv::Mat grayscaled = cv::Mat(img.rows, img.cols, CV_8UC1); //To one channel
        for (int i = 0; i < img.rows; i++)
            for (int j = 0; j < img.cols; j++)
            {
                int b = img.at<Vec3b>(i, j)[0];
                int g = img.at<Vec3b>(i, j)[1];
                int r = img.at<Vec3b>(i, j)[2];

                double newValue = (r * 0.2126 + g * 0.7152 + b * 0.0722);
                grayscaled.at<uchar>(i, j) = newValue;

            }
        return grayscaled;
}
