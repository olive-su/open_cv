#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>


using namespace cv;

Mat image; // �������� -> �ٸ��Լ� ��� �Ұ�

// �ݹ� �Լ� ����
void onMouse(int event, int x, int y, int flags, void* param) 
// �Լ� �Ķ���ʹ� opencv ��ü�� �����Ǿ� �־ �Ķ���ʹ� �����ϰ� �Ѱ������
{			// ���콺 Ŭ�� �̺�Ʈ, ���콺 ��ġ, Ű����, userData
	Point pt(x, y);

	if (event == EVENT_LBUTTONDOWN) {
		rectangle(image, pt, pt + Point(20, 20), Scalar(255, 0, 0), 2);
	}

	imshow("myimage", image);
}

void onChange(int value, void* user_data) {
	int add_value = value;

	image = image + Scalar(0, 0, add_value);
	imshow("myimage", image);
}

int main() {

	image = imread("images\\logo.jpg", IMREAD_UNCHANGED); // �ش� �̹����� grayscale�� ����
	/*
	color = bgrä�� (3ä���� ������ ǥ��)
	grayscale = 1ä�� (1ä���� ����� ǥ��) 0~255, 0 ������ - 255 ���
	*/


	Mat mask(image.size().height, image.size().width, CV_8UC3); // image�� ������ ũ���� mask�� ����� ���� ������ ����
	// mask(w, h, 0~255)

	mask.setTo(0); // �ʱ�ȭ -> �� �ش� ��Ŀ� ���ؼ� Ư�� ������ ġȯ


	Rect rect_area(10, 10, 100, 150);

	rectangle(mask, rect_area, Scalar(0, 0, 255), -1); // -1�� �ϸ� ���� ä���� �簢�� ���

	// ��������, ��������

	// clipping (rect����, mask)
	// ���� ���� -> ���� ��Ʈ����(Region of image)
	Mat clip = image(rect_area);
	// = image ������ �ش��ϴ� ����� ���� �����ϰڴ� (rect_area ������ŭ)
	// �����Ʈ����, ���� -! �����Ʈ������ ���� �׸���, image���� ���� �׷�����.

	// ���� ����
	Mat clip_deepcopy = image(rect_area).clone(); // ���ο� �޸𸮸� ����(mat) ��ȯ

	// ������ (����ũ�� �ִ� ������ �����ؿ� �� ����)
	Mat bitwise_mask(image.size().height, image.size().width, CV_8UC3);
	bitwise_and(image, mask, bitwise_mask);

	// Error) image(3ä��) != mask(1ä��)
	// image 3ä��, 3ä��, ���



	imshow("myimage", image);
	imshow("mymask", mask);
	imshow("myclip", clip);
	imshow("bitwise_mask", bitwise_mask);

	setMouseCallback("myimage", onMouse, 0);
	int value = 50; // �ʱⰪ
	createTrackbar("�÷�����", "myimage", &value, 255, onChange);


	waitKey(0); // delay - ex.33ms -> 30FPS (�ʴ� ������ ��� ��������. ��ȣ ���� ���� ���� ���� �˾Ƽ�!)

	return 0;
}