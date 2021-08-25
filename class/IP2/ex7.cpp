#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


void erode()
{
	Mat image = imread("images\\convfilter.png", IMREAD_GRAYSCALE);

	Mat th_img, dst1;
	threshold(image, th_img, 150, 255, THRESH_BINARY_INV);

	Mat mask(21, 21, CV_8UC1, 1);

	morphologyEx(th_img, dst1, MORPH_ERODE, mask);

	imshow("image", image);
	imshow("������������", th_img);
	imshow("ħ�Ŀ���", dst1);
	waitKey();
	destroyAllWindows();
}


void dilate()
{
	Mat image = imread("images\\convfilter.png", IMREAD_GRAYSCALE);

	Mat th_img, dst1;
	threshold(image, th_img, 150, 255, THRESH_BINARY_INV);

	Mat mask(21, 21, CV_8UC1, 1);

	morphologyEx(th_img, dst1, MORPH_DILATE, mask);

	imshow("image", image);
	imshow("������������", th_img);
	imshow("��â����", dst1);
	waitKey();
	destroyAllWindows();
}


void main()
{
	cout << "erode-------------------------------\n\n";
	erode();
	cout << "dilate-------------------------------\n\n";
	dilate();
}