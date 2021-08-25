// 카메라의 특정 영역에 사각형을 그림
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture capture;
	capture.open(0);											// 0번 카메라 연결
	CV_Assert(capture.isOpened());								// 카메라 연결 예외 처리

	Rect roi(200, 100, 100, 200);

	string title = "카메라 영상에 그리기";						// 윈도우 이름 지정
	while(true) {
		Mat frame;
		capture >> frame;										// 카메라 영상받기

		frame(roi) += Scalar(0, 50, 50);

		rectangle(frame, roi, Scalar(0, 0, 255), 3);
		imshow(title, frame);
		if (waitKey(30) >= 0) break;
	}
	return 0;
}