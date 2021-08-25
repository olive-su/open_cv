#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string  title = "���󺯰�";					// �������� ����
Mat  image;

void onChange(int  value, void* userdata)
{
	int  add_value = value - 130;
	cout << "�߰� ȭ�Ұ� " << add_value << endl;

	Mat tmp = image + add_value;
	imshow(title, tmp);
}

int main()
{
	int  value = 128;
	image = Mat(300, 400, CV_8UC1, Scalar(120));

	namedWindow(title, WINDOW_AUTOSIZE);				// ������ ����
	createTrackbar("��Ⱚ", title, &value, 255, onChange);	// Ʈ���� ���

	imshow(title, image);

	while (1) {
		int key = waitKeyEx(50); // 3.1���� ���ʹ� waitKey�δ� ȭ��ǥ �Է��� ������ ����
		
		//(Left: 2424832 Up : 2490368 Right : 2555904 Down : 2621440)
		if (key == 2555904) {
			setTrackbarPos("��Ⱚ", title, ++value);
			onChange(value, 0);
		}
		else if (key == 2424832) {
			setTrackbarPos("��Ⱚ", title, --value);
			onChange(value, 0);
		}
		if (key == 32) break; // spacebar
	}

	return 0;
}

