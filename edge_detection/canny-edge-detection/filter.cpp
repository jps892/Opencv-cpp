#include "filter.hpp"

cv::Mat filter(cv::Mat input, cv::Mat &filteredImg)
{
    vector<vector<double> > filter = createFilter(3, 3, 1);
    cv::Mat gFiltered = cv::Mat(useFilter(input, filter)); //Gaussian Filter

    //Sobel X Filter
    double x1[] = {-1.0, 0, 1.0};
    double x2[] = {-2.0, 0, 2.0};
    double x3[] = {-1.0, 0, 1.0};

    vector<vector<double> > xFilter(3);
    xFilter[0].assign(x1, x1+3);
    xFilter[1].assign(x2, x2+3);
    xFilter[2].assign(x3, x3+3);

    //Sobel Y Filter
    double y1[] = {1.0, 2.0, 1.0};
    double y2[] = {0, 0, 0};
    double y3[] = {-1.0, -2.0, -1.0};

    vector<vector<double> > yFilter(3);
    yFilter[0].assign(y1, y1+3);
    yFilter[1].assign(y2, y2+3);
    yFilter[2].assign(y3, y3+3);

    //Limit Size
    int size = (int)xFilter.size()/2;

    filteredImg = cv::Mat(gFiltered.rows - 2*size, gFiltered.cols - 2*size, CV_8UC1);

    cv::Mat angles = cv::Mat(gFiltered.rows - 2*size, gFiltered.cols - 2*size, CV_32FC1);

    for (int i = size; i < gFiltered.rows - size; i++)
    {
        for (int j = size; j < gFiltered.cols - size; j++)
        {
            double sumx = 0;
            double sumy = 0;

            for (int x = 0; x < xFilter.size(); x++)
                for (int y = 0; y < xFilter.size(); y++)
                {
                    sumx += xFilter[x][y] * (double)(gFiltered.at<uchar>(i + x - size, j + y - size)); //Sobel_X Filter Value
                    sumy += yFilter[x][y] * (double)(gFiltered.at<uchar>(i + x - size, j + y - size)); //Sobel_Y Filter Value
                }
            double sumxsq = sumx*sumx;
            double sumysq = sumy*sumy;

            double sq2 = sqrt(sumxsq + sumysq);

            if(sq2 > 255) //Unsigned Char Fix
                sq2 =255;
            filteredImg.at<uchar>(i-size, j-size) = sq2;

            if(sumx==0) //Arctan Fix
                angles.at<float>(i-size, j-size) = 90;
            else
                angles.at<float>(i-size, j-size) = atan(sumy/sumx);
        }
    }

    return angles;
}


vector<vector<double> > createFilter(int row, int column, double sigmaIn)
{
    vector<vector<double> > f;

    for (int i = 0; i < row; i++)
    {
        vector<double> col;
        for (int j = 0; j < column; j++)
        {
            col.push_back(-1);
        }
        f.push_back(col);
    }

    float coordSum = 0;
    float constant = 2.0 * sigmaIn * sigmaIn;

    // Sum is for normalization
    float sum = 0.0;

    for (int x = - row/2; x <= row/2; x++)
    {
        for (int y = -column/2; y <= column/2; y++)
        {
            coordSum = (x*x + y*y);
            f[x + row/2][y + column/2] = (exp(-(coordSum) / constant)) / (M_PI * constant);
            sum += f[x + row/2][y + column/2];
        }
    }

    // Normalize the Filter
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            f[i][j] /= sum;

    return f;

}

cv::Mat useFilter(cv::Mat img_in, vector<vector<double> > filterIn)
{
    int size = (int)filterIn.size()/2;
    cv::Mat filteredImg = cv::Mat(img_in.rows - 2*size, img_in.cols - 2*size, CV_8UC1);
    for (int i = size; i < img_in.rows - size; i++)
    {
        for (int j = size; j < img_in.cols - size; j++)
        {
            double sum = 0;

            for (int x = 0; x < filterIn.size(); x++)
                for (int y = 0; y < filterIn.size(); y++)
                {
                    sum += filterIn[x][y] * (double)(img_in.at<uchar>(i + x - size, j + y - size));
                }

            filteredImg.at<uchar>(i-size, j-size) = sum;
        }

    }
    return filteredImg;
}
