#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void corner_harris(Mat image, Mat& corner, int blockSize, int ksize, float k)
{
	Mat dx, dy;
	Mat dx2(image.size(), CV_32F, Scalar(0));
	Mat dy2(image.size(), CV_32F, Scalar(0));
	Mat dxy(image.size(), CV_32F, Scalar(0));

	corner = Mat(image.size(), CV_32F, Scalar(0));

	Sobel(image, dx, CV_32F, 1, 0, ksize);
	Sobel(image, dy, CV_32F, 0, 1, ksize);

	multiply(dx, dx, dx2);
	multiply(dy, dy, dy2);
	multiply(dx, dy, dxy);

	Size msize(5, 5);
	GaussianBlur(dx2, dx2, msize, 0);
	GaussianBlur(dy2, dy2, msize, 0);
	GaussianBlur(dxy, dxy, msize, 0);

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++)
		{
			float  a = dx2.at<float>(i, j);
			float  b = dy2.at<float>(i, j);
			float  c = dxy.at<float>(i, j);

			float det = (a * b - c * c);
			float trace2 = (a + b) * (a + b);
			corner.at<float>(i, j) = det - k * trace2;
		}
	}
}

void draw_coner(Mat corner, Mat& image, int thresh)
{
	int cnt = 0;

	double minv, maxv;
	minMaxLoc(corner, &minv, &maxv);
	cout << format("%10.5f %10.5f\n", minv, maxv);

	normalize(corner, corner, 0, 1000, CV_MINMAX, CV_32FC1, Mat());

	cout << mean(corner) << endl;

	for (int i = 1; i < corner.rows - 1; i++) {
		for (int j = 1; j < corner.cols - 1; j++)
		{
			float cur = corner.at<float>(i, j);
			if (cur > thresh)
			{
				if (cur > corner.at<float>(i - 1, j) &&
					cur > corner.at<float>(i + 1, j) &&
					cur > corner.at<float>(i, j - 1) &&
					cur > corner.at<float>(i, j + 1)) {

					circle(image, Point(j, i), 5, Scalar(0, 0, 255), -1);
					cnt++;
				}
			}
		}
	}
	cout << "ÄÚ³Ê¼ö: " << cnt << endl;
}

Mat image, corner1, corner2, corner3;
int  thresh;

void cornerHarris_demo(int, void*)
{
	Mat img1 = image.clone();
	Mat img2 = image.clone();
	draw_coner(corner1, img1, thresh);
	draw_coner(corner2, img2, thresh);

	imshow("img1-haris", img1);
	imshow("img2-OpenCV harris", img2);
}

int main()
{
	image = imread("images\\logo.jpg", IMREAD_COLOR);
	CV_Assert(image.data);

	int blockSize = 2;
	int apertureSize = 3;
	float k = 0.04f;
	thresh = 50;
	Mat gray;

	cvtColor(image, gray, CV_BGR2GRAY);

	corner_harris(gray, corner1, blockSize, apertureSize, k); // Custom
	cornerHarris(gray, corner2, blockSize, apertureSize, k); // OpenCV

	imshow("image", image);
	imshow("gray", gray);
	createTrackbar("Threshold: ", "image", &thresh, 1000, cornerHarris_demo);

	cornerHarris_demo(0, 0);
	waitKey();
}