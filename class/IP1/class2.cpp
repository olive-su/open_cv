#include "opencv2/highgui.hpp"
#include <iostream>
// highgui opencv 제공하는 gui 기능을 사용하려고 include

using namespace cv;
using namespace std;

void main()
{
	/* Mat 클래스에서 제공하는 at이라는 메소드를 이용해서
	특정 위치의 픽셀값에 접근하는 것
	특정 위치의 픽셀값을 갱신하는 것
	*/

	Mat mat1(5, 5, CV_8UC1);
	Mat resmat(5, 5, CV_8UC1);

	for (int i = 0; i < mat1.rows; i++) {
		for (int j = 0; j < mat1.cols; j++) {
			mat1.at<uchar>(i, j) = j;
			/*
			.at<자료형>(x,y) = 값 -> ch 1개, 8U
			.at<Vec3i>(x, y)[0] = 값 b채널에 대한 값
			.at<Vec3i>(x, y)[1] = 값 g채널에 대한 값
			*/
		}
	}

	clock_t proctime = clock(); // 시작 시간

	// 프로세싱
	resmat.setTo(0); // dummy 값이 들어가지 않도록 초기화
	for (int i = 0; i < mat1.rows; i++) {
		for (int j = 0; j < mat1.cols; j++) {
			if (mat1.at<uchar>(i, j) > 2) {
					resmat.at<uchar>(i, j) = 10;
			}
		}
	}

	clock_t proctime_end = clock(); // 종료 시간

	double elapsed_secs = double(proctime_end - proctime) / CLOCKS_PER_SEC;
	cout << "processing time:" << elapsed_secs << endl;
	// 시간 측정. 너무 짧으면 0으로 판단되어 안나타남

	Mat reducemat;
	reduce(resmat, reducemat, 1, REDUCE_AVG);

	Mat image = imread();
	Rect rect_target(0, 0, 100, 200);
	Mat roi = image(rect_target);
	Scalar value = mean(roi, mask); // mask를 만들어서 연산에 접근할 수 있다.
	
	Scalar mean;
	Scalar stddev;
	meanStdDev(image, mean, stddev, mask); // output Array가 mean param 이다! 따라서 리턴값 X


	cout << mat1 << endl;
	cout << resmat << endl;
	cout << reducemat << endl;
}