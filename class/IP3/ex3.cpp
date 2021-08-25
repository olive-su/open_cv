#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void scaling(Mat  img, Mat& dst, Size size)			// 크기 변경 함수
{
	dst = Mat(size, img.type(), Scalar(0));				
	double ratioY = (double)size.height / img.rows;	
	double ratioX = (double)size.width / img.cols;		

	for (int i = 0; i < img.rows; i++) {				//순방향 사상
		for (int j = 0; j < img.cols; j++)
		{
			int x = (int)(j * ratioX);
			int y = (int)(i * ratioY);
			dst.at<uchar>(y, x) = img.at<uchar>(i, j);
		}
	}
}

void forwardmapping() {
	Mat image = imread("images\\road_2.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat dst1, dst2;
	scaling(image, dst1, Size(image.size().width / 2, image.size().height / 2));		// 축소
	scaling(image, dst2, Size(image.size().width * 2, image.size().height * 2));		// 확대

	imshow("image", image);
	imshow("dst1-축소", dst1);
	imshow("dst2-확대", dst2);
	waitKey();
	destroyAllWindows();
}

void scaling_nearest(Mat  img, Mat& dst, Size size)		// 최근접 이웃 보간 
{
	dst = Mat(size, CV_8U, Scalar(0));
	double ratioY = (double)size.height / img.rows;
	double ratioX = (double)size.width / img.cols;

	for (int i = 0; i < dst.rows; i++) {				//  역방향 사상
		for (int j = 0; j < dst.cols; j++)
		{
			int x = (int)cvRound(j / ratioX) - 1;
			int y = (int)cvRound(i / ratioY) - 1;
			if (x < 0) { x = 0; }
			if (y < 0) { y = 0; }
			dst.at<uchar>(i, j) = img.at<uchar>(y, x);
		}
	}
}

void reversemapping_near() {
	Mat image = imread("images\\road_2.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat dst2;
	scaling_nearest(image, dst2, Size(image.size().width * 2, image.size().height * 2));		// 확대 (최근접이웃)

	imshow("image", image);
	imshow("dst2-확대+최근접이웃", dst2);
	waitKey();
	//destroyAllWindows();
}


uchar bilinear_value(Mat img, double x, double y)	// 양선형 보간
{
	if (x >= img.cols - 1)  x--;
	if (y >= img.rows - 1)  y--;

	Point pt((int)x, (int)y);
	int A = img.at<uchar>(pt);						// 왼쪽상단 화소
	int B = img.at<uchar>(pt + Point(0, 1));		// 왼쪽하단 화소
	int C = img.at<uchar>(pt + Point(1, 0));		// 오른쪽상단 화소
	int D = img.at<uchar>(pt + Point(1, 1));		// 오른쪽하단 화소

	double alpha = y - pt.y;
	double beta = x - pt.x;
	int M1 = A + (int)cvRound(alpha * (B - A));			// 1차 보간
	int M2 = C + (int)cvRound(alpha * (D - C));
	int P = M1 + (int)cvRound(beta * (M2 - M1));		// 2차 보간
	return  saturate_cast<uchar>(P);
}

void scaling_bilinear(Mat  img, Mat& dst, Size size)				// 양선형 보간
{
	dst = Mat(size, img.type(), Scalar(0));
	double ratio_Y = (double)size.height / img.rows;
	double ratio_X = (double)size.width / img.cols;

	for (int i = 0; i < dst.rows; i++) {							// 역방향 사상
		for (int j = 0; j < dst.cols; j++) {
			double y = i / ratio_Y;
			double x = j / ratio_X;
			dst.at<uchar>(i, j) = bilinear_value(img, x, y);		// 화소 양선형 보간
		}
	}
}

void reversemapping_bilinear() {
	Mat image = imread("images\\road_2.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat dst2;
	scaling_bilinear(image, dst2, Size(image.size().width * 2, image.size().height * 2));		// 확대 (최근접이웃)

	imshow("image", image);
	imshow("dst2-확대+양선형보간", dst2);
	waitKey();
	destroyAllWindows();
}

int main()
{
	cout << "forwardmapping-------------------------------\n\n";
	forwardmapping();
	cout << "reversemapping_near-------------------------------\n\n";
	reversemapping_near();
	cout << "reversemapping_bilinear-------------------------------\n\n";
	reversemapping_bilinear();
	return 0;
}