#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void exWindow() {
	Mat image(300, 400, CV_8U);
	image.setTo(100);
	
	namedWindow("������", WINDOW_NORMAL);
	moveWindow("������", 100, 200);
	imshow("������", image);
	cout << waitKey() << endl;

	// ������� ����� ���������
	// ���������� ����� ���� ���������
}

void exWindowColor() {
	Mat image(300, 400, CV_8UC3);
	image.setTo(Scalar(0,0,255));

	namedWindow("������", WINDOW_NORMAL);
	moveWindow("������", 100, 200);
	imshow("������", image);
	waitKey(0);
}

string  title = "���콺 �׸���";
Mat image;

void onMouse(int event, int x, int y, int flags, void* param)
{
	Point pt(x, y);
	static Scalar color(0, 0, 0);
		
	// �⺻���� �ϰ� �߰�
	// and ����
	if (flags & EVENT_FLAG_CTRLKEY) {
		color = Scalar(255, 0, 0);
	}
	// &���� ����
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

string  title_track = "Ʈ����";
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

	// ���콺
	image = Mat(300, 500, CV_8UC3, Scalar(255, 255, 255));
	imshow(title, image);
	setMouseCallback(title, onMouse, 0);
	waitKey(0);

	// Ʈ����
	image_track = Mat(500, 500, CV_8UC3, Scalar(255, 255, 255));
	imshow(title_track, image_track);
	createTrackbar("������", title_track, &thickness, 10, onChange1);	// Ʈ���� ���
	createTrackbar("������", title_track, &radius, 50, onChange1);	// Ʈ���� ���
	setMouseCallback(title_track, onMouseTrack, 0);
	waitKey(0);


	return 0;
}