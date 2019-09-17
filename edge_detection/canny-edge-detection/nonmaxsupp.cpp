#include "nonmaxsupp.hpp"


cv::Mat nonmaxsupp(cv::Mat sFiltered, cv::Mat angles)
{
    cv::Mat nonMaxSupped = cv::Mat(sFiltered.rows-2, sFiltered.cols-2, CV_8UC1);
        for (int i=1; i< sFiltered.rows - 1; i++) {
            for (int j=1; j<sFiltered.cols - 1; j++) {
                float Tangent = angles.at<float>(i,j);

                nonMaxSupped.at<uchar>(i-1, j-1) = sFiltered.at<uchar>(i,j);
                //Horizontal Edge
                if (((-22.5 < Tangent) && (Tangent <= 22.5)) || ((157.5 < Tangent) && (Tangent <= -157.5)))
                {
                    if ((sFiltered.at<uchar>(i,j) < sFiltered.at<uchar>(i,j+1)) || (sFiltered.at<uchar>(i,j) < sFiltered.at<uchar>(i,j-1)))
                        nonMaxSupped.at<uchar>(i-1, j-1) = 0;
                }
                //Vertical Edge
                if (((-112.5 < Tangent) && (Tangent <= -67.5)) || ((67.5 < Tangent) && (Tangent <= 112.5)))
                {
                    if ((sFiltered.at<uchar>(i,j) < sFiltered.at<uchar>(i+1,j)) || (sFiltered.at<uchar>(i,j) < sFiltered.at<uchar>(i-1,j)))
                        nonMaxSupped.at<uchar>(i-1, j-1) = 0;
                }

                //-45 Degree Edge
                if (((-67.5 < Tangent) && (Tangent <= -22.5)) || ((112.5 < Tangent) && (Tangent <= 157.5)))
                {
                    if ((sFiltered.at<uchar>(i,j) < sFiltered.at<uchar>(i-1,j+1)) || (sFiltered.at<uchar>(i,j) < sFiltered.at<uchar>(i+1,j-1)))
                        nonMaxSupped.at<uchar>(i-1, j-1) = 0;
                }

                //45 Degree Edge
                if (((-157.5 < Tangent) && (Tangent <= -112.5)) || ((22.5 < Tangent) && (Tangent <= 67.5)))
                {
                    if ((sFiltered.at<uchar>(i,j) < sFiltered.at<uchar>(i+1,j+1)) || (sFiltered.at<uchar>(i,j) < sFiltered.at<uchar>(i-1,j-1)))
                        nonMaxSupped.at<uchar>(i-1, j-1) = 0;
                }
            }
        }
        return nonMaxSupped;
}
