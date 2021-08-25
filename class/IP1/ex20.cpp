#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void colorCh() {
	Mat image = imread("images\\logo.jpg", IMREAD_COLOR); // 이미지 변경하면서 해보기!
	//Mat image = imread("images\\road_1.png", IMREAD_COLOR);
	Mat splitImage[3];

	split(image, splitImage);

	imshow("ori", image);
	imshow("b", splitImage[0]);
	imshow("g", splitImage[1]);
	imshow("r", splitImage[2]);
	waitKey();
	destroyAllWindows();
}

void colorModel() {
	Mat image = imread("images\\human_1.jpg", IMREAD_COLOR);
	Mat splitImage[3];

	split(image, splitImage);

	imshow("ori", image);
	imshow("b", splitImage[0]);
	imshow("g", splitImage[1]);
	imshow("r", splitImage[2]);

	waitKey();
	destroyAllWindows();

	image = imread("images\\road_4.jpg", IMREAD_COLOR);
	Mat cvtHSL;
	cvtColor(image, cvtHSL, CV_BGR2HLS);
	Mat splitImageHSL[3];

	split(cvtHSL, splitImageHSL);

	imshow("ori", image);
	imshow("hsl", cvtHSL);
	imshow("h", splitImageHSL[0]);
	imshow("l", splitImageHSL[1]);
	imshow("s", splitImageHSL[2]);

	waitKey();
	destroyAllWindows();

	image = imread("images\\road_2.jpg", IMREAD_COLOR);
	Mat cvtYUV;
	cvtColor(image, cvtYUV, CV_BGR2YUV); // CV_BGR2YCrCb, CV_BGR2YCbCr == YUV
	Mat splitImageYUV[3];

	split(cvtYUV, splitImageYUV);

	imshow("ori", image);
	imshow("yuv", cvtYUV);
	imshow("y", splitImageYUV[0]);
	imshow("cb", splitImageYUV[1]);
	imshow("cr", splitImageYUV[2]);

	Mat res = splitImageYUV[1].clone();
	res.setTo(0);
	for (int i = 0; i < splitImageYUV[1].rows; i++) {
		for (int j = 0; j < splitImageYUV[1].cols; j++)
		{
			if (splitImageYUV[2].at<uchar>(i, j) > 128) {
				res.at<uchar>(i, j) = res.at<uchar>(i, j) + 100;
			}
			if (splitImageYUV[1].at<uchar>(i, j) < 128) {
				res.at<uchar>(i, j) = res.at<uchar>(i, j) + 100;
			}
		}
	}
	imshow("res", res);

	waitKey();
	destroyAllWindows();
}

void colorChAt() {
	Mat image = imread("images\\road_3.jpg", IMREAD_COLOR);
	Mat splitImage[3];
	Mat res = image.clone();
	res.setTo(Scalar(0, 0, 0));

	split(image, splitImage);


	clock_t begin = clock();

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++)
		{
			if (image.at<Vec3b>(i, j)[2] > 200
				&& image.at<Vec3b>(i, j)[1] < 50
				&& image.at<Vec3b>(i, j)[0] < 50) {
				res.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << elapsed_secs << endl;


	imshow("ori", image);
	imshow("res", res);
	waitKey();
	destroyAllWindows();
}

void main()
{
	cout << "colorCh-------------------------------\n\n";
	colorCh();
	cout << "colorModel-------------------------------\n\n";
	colorModel();
	cout << "colorChAt-------------------------------\n\n";
	colorChAt();
}
