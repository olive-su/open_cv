#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


void calc_histo(Mat image, Mat& hist, int bins, int range_max = 256)
{
	hist = Mat(bins, 1, CV_32F, Scalar(0));
	float gap = range_max / (float)bins;

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++)
		{
			int idx = int(image.at<uchar>(i, j) / gap);
			hist.at<float>(idx)++;
		}
	}
}

void draw_histo(Mat hist, Mat& hist_img, Size size = Size(256, 200))
{
	hist_img = Mat(size, CV_8U, Scalar(255));
	float  bin = (float)hist_img.cols / hist.rows;
	normalize(hist, hist, 0, size.height, NORM_MINMAX);

	for (int i = 0; i < hist.rows; i++)
	{
		float  start_x = (i * bin);
		float  end_x = (i + 1) * bin;
		Point2f pt1(start_x, 0);
		Point2f pt2(end_x, hist.at <float>(i));

		if (pt2.y > 0)
			rectangle(hist_img, pt1, pt2, Scalar(0), -1);
	}
	flip(hist_img, hist_img, 0);
}


void histo() {
	Mat image = imread("images\\lena.png", IMREAD_GRAYSCALE);
	Mat hist, hist_img;
	calc_histo(image, hist, 256);		// 히스토그램 계산
	draw_histo(hist, hist_img);
	cout << hist.t() << endl;

	imshow("hist_img", hist_img);
	imshow("image", image);
	waitKey();
	destroyAllWindows();
}

void main()
{
	cout << "histo-------------------------------\n\n";
	histo();
}