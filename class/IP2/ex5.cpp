#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Range th1(50, 100), th2(100, 200);								// Ʈ���ٷ� ������ ���� ����
Mat hue, light;													// ����, ��� ä�� ���� ��������

Mat bgr[3];
int thb = 50, thg = 50, thr = 50;								// Ʈ���ٷ� ������ ���� ����

String title = "����ȭ";

void onThreshold(int  value, void* userdata)					// ���� ���� Ʈ���� �ݹ� �Լ�
{
	Mat result = Mat(hue.size(), CV_8U, Scalar(0));

	// ���� ������ ����ȭ ����
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++)
		{
			// ���� ������ ���� ���� ����
			bool ck1 = hue.at<uchar>(i, j) >= th1.start && hue.at<uchar>(i, j) < th1.end;
			bool ck2 = light.at<uchar>(i, j) >= th2.start && light.at<uchar>(i, j) < th2.end;

			result.at<uchar>(i, j) = (ck1 && ck2) ? 255 : 0;		// ������ ����
		}
	}
	imshow(title, result);
}

void hsl() {
	Mat image = imread("images/biglogo.jpg", IMREAD_COLOR);// �÷� ���� �ε�
	CV_Assert(image.data);

	Mat HSV, hsv[3];
	cvtColor(image, HSV, CV_BGR2HLS);			// �÷� ���� ��ȯ
	split(HSV, hsv);										// ä�� �и�
	hsv[0].copyTo(hue);										// hue ��Ŀ� ���� ä�� ����
	hsv[1].copyTo(light);										// light ��Ŀ� ���� ä�� ����

	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar("Hue_th1", title, &th1.start, 180, onThreshold);	// Ʈ���� ���
	createTrackbar("Hue_th2", title, &th1.end, 180, onThreshold);
	createTrackbar("light_th1", title, &th2.start, 256, onThreshold);
	createTrackbar("light_th2", title, &th2.end, 256, onThreshold);

	onThreshold(0, 0);											// ����ȭ ����
	imshow("image", image);
	waitKey(0);
	destroyAllWindows();
}


void th(int  value, void* userdata) {
	Mat result = Mat(bgr[0].size(), CV_8U, Scalar(0));
	Mat tmp = Mat(bgr[0].size(), CV_8U, Scalar(0));

	threshold(bgr[0], tmp, thb, 255, THRESH_BINARY);
	result = result + tmp;
	tmp.setTo(0);
	threshold(bgr[1], tmp, thg, 255, THRESH_BINARY);
	result = result + tmp;
	tmp.setTo(0);
	threshold(bgr[2], tmp, thr, 255, THRESH_BINARY);
	result = result + tmp;
	tmp.setTo(0);

	imshow(title, result);
}

void rgb() {
	Mat image = imread("images/biglogo.jpg", IMREAD_COLOR);// �÷� ���� �ε�
	CV_Assert(image.data);

	split(image, bgr);

	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar("B_th", title, &thb, 256, th);	// Ʈ���� ���
	createTrackbar("G_th", title, &thg, 256, th);
	createTrackbar("R_th", title, &thr, 256, th);

	th(0,0);											// ����ȭ ����
	imshow("image", image);
	waitKey(0);
}

int main()
{
	hsl();
	rgb();
	return 0;
}