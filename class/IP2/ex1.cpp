#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void sample() {
	Mat image = imread("images\\xray.jpg", IMREAD_GRAYSCALE);
	Mat convertedImage;

	applyColorMap(image, convertedImage, COLORMAP_JET);
	imshow("gray", image);
	imshow("image", convertedImage);
	waitKey(0);
	destroyAllWindows();
}

void lut() {
	Mat image = imread("images\\xray.jpg", IMREAD_COLOR);

	unsigned char b[] = { 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,253,251,249,247,245,242,241,238,237,235,233,231,229,227,225,223,221,219,217,215,213,211,209,207,205,203,201,199,197,195,193,191,189,187,185,183,181,179,177,175,173,171,169,167,165,163,161,159,157,155,153,151,149,147,145,143,141,138,136,134,132,131,129,126,125,122,121,118,116,115,113,111,109,107,105,102,100,98,97,94,93,91,89,87,84,83,81,79,77,75,73,70,68,66,64,63,61,59,57,54,52,51,49,47,44,42,40,39,37,34,33,31,29,27,25,22,20,18,17,14,13,11,9,6,4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	unsigned char g[] = { 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,254,252,250,248,246,244,242,240,238,236,234,232,230,228,226,224,222,220,218,216,214,212,210,208,206,204,202,200,198,196,194,192,190,188,186,184,182,180,178,176,174,171,169,167,165,163,161,159,157,155,153,151,149,147,145,143,141,139,137,135,133,131,129,127,125,123,121,119,117,115,113,111,109,107,105,103,101,99,97,95,93,91,89,87,85,83,82,80,78,76,74,72,70,68,66,64,62,60,58,56,54,52,50,48,46,44,42,40,38,36,34,32,30,28,26,24,22,20,18,16,14,12,10,8,6,4,2,0 };
	unsigned char r[] = { 195,194,193,191,190,189,188,187,186,185,184,183,182,181,179,178,177,176,175,174,173,172,171,170,169,167,166,165,164,163,162,161,160,159,158,157,155,154,153,152,151,150,149,148,147,146,145,143,142,141,140,139,138,137,136,135,134,133,131,130,129,128,127,126,125,125,125,125,125,125,125,125,125,125,125,125,125,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126 };

	cv::Mat channels[] = { cv::Mat(256, 1, CV_8U, b), cv::Mat(256, 1, CV_8U, g), cv::Mat(256, 1, CV_8U, r) };
	cv::Mat lut; // Create a lookup table
	cv::merge(channels, 3, lut);

	cv::Mat im_color(image.size(), CV_8UC3);
	cv::LUT(image, lut, im_color);

	imshow("gray", image);
	imshow("res", im_color);
	waitKey(0);
	destroyAllWindows();
}

void lut2() {
	Mat image = imread("images\\xray.jpg", IMREAD_COLOR);

	Mat res(image.size(), CV_8UC3);
	Mat lookUpTable(1, 256, CV_8UC3);
	lookUpTable.setTo(Scalar(0, 0, 0));

	// create a matrix for lookup
	for (int i = 50; i < 150; ++i) {
		lookUpTable.at<Vec3b>(0, i)[2] = saturate_cast<uchar>(255);
	}
	for (int i = 10; i < 50; ++i) {
		lookUpTable.at<Vec3b>(0, i)[0] = saturate_cast<uchar>(255);
	}
	for (int i = 150; i < 255; ++i) {
		lookUpTable.at<Vec3b>(0, i)[1] = saturate_cast<uchar>(255);
	}

	LUT(image, lookUpTable, res);

	imshow("gray", image);
	imshow("res", res);
	waitKey(0);
	destroyAllWindows();
}

void peek() {
	Mat image = imread("images/sign_1.jpg", IMREAD_COLOR);
	Mat ch[3];
	Mat res;

	split(image, ch);

	inRange(ch[0], 200, 255, ch[0]);
	inRange(ch[1], 200, 255, ch[1]);
	inRange(ch[2], 200, 255, ch[2]);

	merge(ch, 3, res);

	imshow("color", image);
	imshow("res", res);
	waitKey(0);
	destroyAllWindows();
}

void peek2() {
	Mat image = imread("images/sign_1.jpg", IMREAD_GRAYSCALE);
	Mat res(image.size(), image.type());

	for (int i = 0; i < res.rows; i++) {
		for (int j = 0; j < res.cols; j++)
		{
			if (image.at<uchar>(i, j) > 128 && image.at<uchar>(i, j) < 255) {
				res.at<uchar>(i, j) = 255;
			}
			else {
				res.at<uchar>(i, j) = 0;
			}
		}
	}

	imshow("gray", image);
	imshow("res", res);
	waitKey(0);
	destroyAllWindows();
}

void main()
{
	cout << "sample-------------------------------\n\n";
	sample();
	cout << "LUT-------------------------------\n\n";
	lut();
	cout << "LUT2-------------------------------\n\n";
	lut2();
	cout << "peek-------------------------------\n\n";
	peek();
	cout << "peek2-------------------------------\n\n";
	peek2();
}