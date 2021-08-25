#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void differOp(Mat img, Mat& dst, int mask_size)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	Point h_m(mask_size / 2, mask_size / 2);

	for (int i = h_m.y; i < img.rows - h_m.y; i++) {
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			vector<uchar> mask;
			for (int u = 0; u < mask_size; u++) {
				for (int v = 0; v < mask_size; v++) {
					int y = i + u - h_m.y;
					int x = j + v - h_m.x;
					mask.push_back(img.at<uchar>(y, x));
				}
			}

			uchar max = 0;
			for (int k = 0; k < (int)mask.size() / 2; k++)
			{
				int start = mask[k];
				int end = mask[mask.size() - k - 1];

				uchar difference = abs(start - end);
				if (difference > max)  max = difference;
			}
			dst.at<uchar>(i, j) = max;
		}
	}
}

void diff() {
	Mat image = imread("images\\lena.png", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat edge;
	differOp(image, edge, 3);

	imshow("image", image);
	imshow("diff edge", edge);
	waitKey();
	destroyAllWindows();
}


void filter(Mat img, Mat& dst, Mat mask)
{
	dst = Mat(img.size(), CV_32F, Scalar(0));
	Point h_m = mask.size() / 2;

	for (int i = h_m.y; i < img.rows - h_m.y; i++) {
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			float sum = 0;
			for (int u = 0; u < mask.rows; u++) {
				for (int v = 0; v < mask.cols; v++)
				{
					int y = i + u - h_m.y;
					int x = j + v - h_m.x;
					sum += img.at<uchar>(y, x) * mask.at<float>(u, v);
				}
			}
			dst.at<float>(i, j) = sum;
		}
	}
}

void differential(Mat image, Mat& dst, float data1[], float data2[])
{
	Mat dst1, dst2, add;
	Mat mask1(3, 3, CV_32F, data1);				
	Mat mask2(3, 3, CV_32F, data2);

	filter(image, dst1, mask1);					// 사용자 정의 회선 함수
	filter(image, dst2, mask2);
	// sqrt((x2 - x1)^2 + (y2 - y1)^2)
	magnitude(dst1, dst2, dst);					// 회선 결과 두 행렬의 크기 계산

	dst1 = abs(dst1);							// 절대값
	dst2 = abs(dst2);
	dst1.convertTo(dst1, CV_8U);				// 형변환
	dst2.convertTo(dst2, CV_8U);

	add = dst1 + dst2;
	imshow("dst1", dst1);
	imshow("dst2", dst2);
	imshow("add", add);
}

void roberts() {
	Mat image = imread("images\\lena.png", IMREAD_GRAYSCALE);

	float data1[] = {
		-1, 0, 0,
		0, 1, 0,
		0, 0, 0
	};
	float data2[] = {
		0, 0, -1,
		0, 1, 0,
		0, 0, 0
	};

	Mat dst;
	differential(image, dst, data1, data2);

	imshow("image", image);
	dst.convertTo(dst, CV_8U);
	imshow("roberts edge", dst);
	waitKey(0);
	destroyAllWindows();

}

void sobel() {
	Mat image = imread("images\\lena.png", IMREAD_GRAYSCALE);

	float data1[] = {
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1
	};
	float data2[] = {
		-1, -2, -1,
		0, 0, 0,
		1, 2, 1
	};

	Mat dst;
	differential(image, dst, data1, data2);

	imshow("image", image);
	dst.convertTo(dst, CV_8U);
	imshow("sobel edge", dst);
	waitKey(0);
	destroyAllWindows();

}

void laplacian() {
	Mat image = imread("images\\lena.png", IMREAD_GRAYSCALE);

	short data1[] = {
		0, 1, 0,
		1, -4, 1,
		0, 1, 0
	};
	short data2[] = {
		-1, -1, -1,
		-1, 8, -1,
		-1, -1, -1
	};

	Mat dst1, dst2, dst3;
	Mat  mask4(3, 3, CV_16S, data1);
	Mat  mask8(3, 3, CV_16S, data2);

	filter2D(image, dst1, CV_16S, mask4);
	filter2D(image, dst2, CV_16S, mask8);

	convertScaleAbs(dst1, dst1);
	convertScaleAbs(dst2, dst2);
	convertScaleAbs(dst3, dst3);

	imshow("image", image);
	imshow("filter 4방향", dst1);
	imshow("filter 8방향", dst2);
	waitKey(0);
	destroyAllWindows();

}

void DOG() {
	Mat image = imread("images\\lena.png", IMREAD_GRAYSCALE);

	Mat dst3, dst4;

	GaussianBlur(image, dst3, Size(1, 1), 0.0);
	GaussianBlur(image, dst4, Size(9, 9), 1.6);
	Mat dst_DoG = dst3 - dst4;

	normalize(dst_DoG, dst_DoG, 0, 255, CV_MINMAX);

	imshow("image", image);
	imshow("DOG_gaussianblur", dst_DoG);
	waitKey(0);
	destroyAllWindows();
}

void main()
{
	cout << "diff-------------------------------\n\n";
	diff();
	cout << "roberts-------------------------------\n\n";
	roberts();
	cout << "sobel-------------------------------\n\n";
	sobel();
	cout << "laplacian-------------------------------\n\n";
	laplacian();
	cout << "DOG-------------------------------\n\n";
	DOG();
}