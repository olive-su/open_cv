#include "opencv2/highgui.hpp"
#include <iostream>
// highgui opencv �����ϴ� gui ����� ����Ϸ��� include

using namespace cv;
using namespace std;

void main()
{
	/* Mat Ŭ�������� �����ϴ� at�̶�� �޼ҵ带 �̿��ؼ�
	Ư�� ��ġ�� �ȼ����� �����ϴ� ��
	Ư�� ��ġ�� �ȼ����� �����ϴ� ��
	*/

	Mat mat1(5, 5, CV_8UC1);
	Mat resmat(5, 5, CV_8UC1);

	for (int i = 0; i < mat1.rows; i++) {
		for (int j = 0; j < mat1.cols; j++) {
			mat1.at<uchar>(i, j) = j;
			/*
			.at<�ڷ���>(x,y) = �� -> ch 1��, 8U
			.at<Vec3i>(x, y)[0] = �� bä�ο� ���� ��
			.at<Vec3i>(x, y)[1] = �� gä�ο� ���� ��
			*/
		}
	}

	clock_t proctime = clock(); // ���� �ð�

	// ���μ���
	resmat.setTo(0); // dummy ���� ���� �ʵ��� �ʱ�ȭ
	for (int i = 0; i < mat1.rows; i++) {
		for (int j = 0; j < mat1.cols; j++) {
			if (mat1.at<uchar>(i, j) > 2) {
					resmat.at<uchar>(i, j) = 10;
			}
		}
	}

	clock_t proctime_end = clock(); // ���� �ð�

	double elapsed_secs = double(proctime_end - proctime) / CLOCKS_PER_SEC;
	cout << "processing time:" << elapsed_secs << endl;
	// �ð� ����. �ʹ� ª���� 0���� �ǴܵǾ� �ȳ�Ÿ��

	Mat reducemat;
	reduce(resmat, reducemat, 1, REDUCE_AVG);

	Mat image = imread();
	Rect rect_target(0, 0, 100, 200);
	Mat roi = image(rect_target);
	Scalar value = mean(roi, mask); // mask�� ���� ���꿡 ������ �� �ִ�.
	
	Scalar mean;
	Scalar stddev;
	meanStdDev(image, mean, stddev, mask); // output Array�� mean param �̴�! ���� ���ϰ� X


	cout << mat1 << endl;
	cout << resmat << endl;
	cout << reducemat << endl;
}