#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void exWindow() {
	Mat image(300, 400, CV_8U);
	image.setTo(100);
	
	namedWindow("윈도우", WINDOW_NORMAL);
	moveWindow("윈도우", 100, 200);
	imshow("윈도우", image);
	cout << waitKey() << endl;

	// 흰색으로 배경을 띄워보세요
	// 검은색으로 배경을 만들어서 띄워보세요
}

void exWindowColor() {
	Mat image(300, 400, CV_8UC3);
	image.setTo(Scalar(0,0,255));

	namedWindow("윈도우", WINDOW_NORMAL);
	moveWindow("윈도우", 100, 200);
	imshow("윈도우", image);
	waitKey(0);
}

string  title = "마우스 그리기";
Mat image;

void onMouse(int event, int x, int y, int flags, void* param)
{
	Point pt(x, y);
	static Scalar color(0, 0, 0);
		
	// 기본으로 하고 추가
	// and 연산
	if (flags & EVENT_FLAG_CTRLKEY) {
		color = Scalar(255, 0, 0);
	}
	// &연산 설명
	else if ((flags & EVENT_FLAG_SHIFTKEY) == EVENT_FLAG_SHIFTKEY) {
		color = Scalar(0, 0, 255);
	}
	else if (flags & EVENT_FLAG_ALTKEY) {
		color = Scalar(0, 255, 0);
	}
	else color = Scalar(0, 0, 0);

	if (event == EVENT_LBUTTONDOWN) {
		circle(image, pt, 5, color, 1);
	}
	else if (event == EVENT_RBUTTONDOWN) {
		rectangle(image, pt, pt + Point(30, 30), color, 2);
	}
	imshow(title, image);
}

string  title_track = "트랙바";
Mat image_track;
int thickness = 3, radius = 20;

void onChange1(int  value, void* userdata) {  }
void onChange2(int  value, void* userdata) {  }

void onMouseTrack(int event, int x, int y, int flags, void* param)
{
	Point pt(x, y);
	static Scalar colortrack(0, 0, 0);
	if (flags & EVENT_FLAG_CTRLKEY) {
		colortrack = Scalar(255, 0, 0);
	}
	else if (flags & EVENT_FLAG_SHIFTKEY) {
		colortrack = Scalar(0, 0, 255);
	}
	else colortrack = Scalar(0, 0, 0);

	if (event == EVENT_LBUTTONDOWN) {
		circle(image_track, pt, radius, colortrack, thickness);
	}
	else if (event == EVENT_RBUTTONDOWN) {
		rectangle(image_track, pt, pt + Point(radius, radius), colortrack, thickness);
	}

	imshow(title_track, image_track);
}

int main()
{
	exWindow();
	exWindowColor();

	// 마우스
	image = Mat(300, 500, CV_8UC3, Scalar(255, 255, 255));
	imshow(title, image);
	setMouseCallback(title, onMouse, 0);
	waitKey(0);

	// 트랙바
	image_track = Mat(500, 500, CV_8UC3, Scalar(255, 255, 255));
	imshow(title_track, image_track);
	createTrackbar("선굵기", title_track, &thickness, 10, onChange1);	// 트랙바 등록
	createTrackbar("반지름", title_track, &radius, 50, onChange1);	// 트랙바 등록
	setMouseCallback(title_track, onMouseTrack, 0);
	waitKey(0);


	return 0;
}