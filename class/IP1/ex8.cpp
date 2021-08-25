// ī�޶��� Ư�� ������ �簢���� �׸�
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture capture;
	capture.open(0);											// 0�� ī�޶� ����
	CV_Assert(capture.isOpened());								// ī�޶� ���� ���� ó��

	Rect roi(200, 100, 100, 200);

	string title = "ī�޶� ���� �׸���";						// ������ �̸� ����
	while(true) {
		Mat frame;
		capture >> frame;										// ī�޶� ����ޱ�

		frame(roi) += Scalar(0, 50, 50);

		rectangle(frame, roi, Scalar(0, 0, 255), 3);
		imshow(title, frame);
		if (waitKey(30) >= 0) break;
	}
	return 0;
}