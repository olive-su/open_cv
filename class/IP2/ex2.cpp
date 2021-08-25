#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void op() {
	Mat image = imread("images\\lena.png", IMREAD_GRAYSCALE);

	imshow("gray", image);
	imshow("add+40", image + 40);
	imshow("sub-40", image - 40);
	imshow("mul*3", image * 3);
	imshow("div/3", image / 3);
	imshow("255-inv", 255 - image);
	waitKey(0);
	destroyAllWindows();
}

void op_nonlinear() {
	Mat image = imread("images\\lena.png", IMREAD_GRAYSCALE);
	Mat res(image.size(), image.type());
	float gamma = 0.5; //밝게, 1 동일, 2 어둡게
	for (int i = 0; i < res.rows; i++) {
		for (int j = 0; j < res.cols; j++)
		{
			res.at<uchar>(i, j) = saturate_cast<uchar>(pow((float)(image.at<uchar>(i, j) / 255.0), gamma) * 255.0f);
		}
	}
	imshow("gray", image);
	imshow("gamma", res);
	waitKey(0);
	destroyAllWindows();
}

void blending() {
	Mat image1 = imread("images\\lena.png", IMREAD_GRAYSCALE);
	Mat image2 = imread("images\\biglogo.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!(image1.empty() || image2.empty()));

	double alpha = 0.6, beta = 0.7;

	Mat add_img1 = image1 + image2;
	Mat add_img2 = image1 * 0.5 + image2 * 0.5;
	Mat add_img3 = image1 * alpha + image2 * (1 - alpha);

	Mat add_img4, sub_img1, sub_img2;;
	addWeighted(image1, alpha, image2, beta, 0, add_img4);

	imshow("image1", image1);
	imshow("image2", image2);
	imshow("add_img1", add_img1);
	imshow("add_img2", add_img2);
	imshow("add_img3", add_img3);
	imshow("add_img4", add_img4);
	waitKey();
	destroyAllWindows();
}


void contrast() {
	Mat image = imread("images\\lena.png", IMREAD_GRAYSCALE);

	Scalar avg = mean(image) / 2.0;					// 원본 영상 화소 평균의 절반
	Mat dst1 = image * 0.5;							// 명암대비 감소
	Mat dst2 = image * 2.0;							// 명암대비 증가
	Mat dst3 = image * 0.5 + avg[0];				// 영상 평균 이용 대비 감소
	Mat dst4 = image * 2.0 - avg[0];				// 영상 평균 이용 대비 중가

	imshow("image", image);
	imshow("dst1-대비감소", dst1);
	imshow("dst2-대비증가", dst2);
	imshow("dst3-평균이용 대비감소", dst3);
	imshow("dst4-평균이용 대비증가", dst4);
	waitKey();
	destroyAllWindows();
}


void mask() {
	Mat image = imread("images\\lena.png", IMREAD_GRAYSCALE);
	Mat res(image.size(), image.type());
	Mat mask(image.size(), image.type());
	mask.setTo(0);


	Point2d center(image.size().width / 2.0, image.size().height / 2.0);		// 두 좌표 중심

	ellipse(mask, center, Size(50,50), 0, 0, 360, Scalar(1), -1);

	multiply(image, mask, res);

	mask = mask * 255;

	imshow("gray", image);
	imshow("mask", mask);
	imshow("res", res);
	waitKey(0);
	destroyAllWindows();
}

void bitwiseAnd() {
	Mat image = imread("images\\lena.png", IMREAD_GRAYSCALE);
	Mat res(image.size(), image.type());
	Mat mask(image.size(), image.type());
	mask.setTo(0);


	Point2d center(image.size().width / 2.0, image.size().height / 2.0);		// 두 좌표 중심

	ellipse(mask, center, Size(50, 50), 0, 0, 360, Scalar(255), -1);

	bitwise_and(image, mask, res);

	imshow("gray", image);
	imshow("mask", mask);
	imshow("res", res);
	waitKey(0);
	destroyAllWindows();
}

void main()
{
	cout << "op-------------------------------\n\n";
	op();
	cout << "op_nonlinear-------------------------------\n\n";
	op_nonlinear();
	cout << "blending-------------------------------\n\n";
	blending();
	cout << "contrast-------------------------------\n\n";
	contrast();

	cout << "mask-------------------------------\n\n";
	mask();
	cout << "bitwiseAnd-------------------------------\n\n";
	bitwiseAnd();
}