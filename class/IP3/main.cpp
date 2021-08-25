#include "opencv2/highgui.hpp"

using namespace cv;

void main()
{
	Mat  image(300, 400, CV_8UC1, cv::Scalar(130));
	imshow("영상보기", image);
	waitKey(0);
}