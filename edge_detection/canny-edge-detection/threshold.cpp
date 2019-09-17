#include "threshold.hpp"
using namespace std;
using namespace cv;

cv::Mat threshold(cv::Mat imgin,int low, int high)
{
    if(low > 255)
        low = 255;
    if(high > 255)
        high = 255;

    Mat EdgeMat = Mat(imgin.rows, imgin.cols, imgin.type());

    for (int i=0; i<imgin.rows; i++)
    {
        for (int j = 0; j<imgin.cols; j++)
        {
            EdgeMat.at<uchar>(i,j) = imgin.at<uchar>(i,j);
            if(EdgeMat.at<uchar>(i,j) > high)
                EdgeMat.at<uchar>(i,j) = 255;
            else if(EdgeMat.at<uchar>(i,j) < low)
                EdgeMat.at<uchar>(i,j) = 0;
            else
            {
                bool anyHigh = false;
                bool anyBetween = false;
                for (int x=i-1; x < i+2; x++)
                {
                    for (int y = j-1; y<j+2; y++)
                    {
                        if(x <= 0 || y <= 0 || EdgeMat.rows || y > EdgeMat.cols) //Out of bounds
                            continue;
                        else
                        {
                            if(EdgeMat.at<uchar>(x,y) > high)
                            {
                                EdgeMat.at<uchar>(i,j) = 255;
                                anyHigh = true;
                                break;
                            }
                            else if(EdgeMat.at<uchar>(x,y) <= high && EdgeMat.at<uchar>(x,y) >= low)
                                anyBetween = true;
                        }
                    }
                    if(anyHigh)
                        break;
                }
                if(!anyHigh && anyBetween)
                    for (int x=i-2; x < i+3; x++)
                    {
                        for (int y = j-1; y<j+3; y++)
                        {
                            if(x < 0 || y < 0 || x > EdgeMat.rows || y > EdgeMat.cols) //Out of bounds
                                continue;
                            else
                            {
                                if(EdgeMat.at<uchar>(x,y) > high)
                                {
                                    EdgeMat.at<uchar>(i,j) = 255;
                                    anyHigh = true;
                                    break;
                                }
                            }
                        }
                        if(anyHigh)
                            break;
                    }
                if(!anyHigh)
                    EdgeMat.at<uchar>(i,j) = 0;
            }
        }
    }
    return EdgeMat;
}
