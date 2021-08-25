#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string  title = "색상변경";					// 전역변수 선언
Mat  image;

void onChange(int  value, void* userdata)
{
	int  add_value = value - 130;
	cout << "추가 화소값 " << add_value << endl;

	Mat tmp = image + add_value;
	imshow(title, tmp);
}

int main()
{
	int  value = 128;
	image = Mat(300, 400, CV_8UC1, Scalar(120));

	namedWindow(title, WINDOW_AUTOSIZE);				// 윈도우 생성
	createTrackbar("밝기값", title, &value, 255, onChange);	// 트렉바 등록

	imshow(title, image);

	while (1) {
		int key = waitKeyEx(50); // 3.1버전 부터는 waitKey로는 화살표 입력이 들어오지 않음
		
		//(Left: 2424832 Up : 2490368 Right : 2555904 Down : 2621440)
		if (key == 2555904) {
			setTrackbarPos("밝기값", title, ++value);
			onChange(value, 0);
		}
		else if (key == 2424832) {
			setTrackbarPos("밝기값", title, --value);
			onChange(value, 0);
		}
		if (key == 32) break; // spacebar
	}

	return 0;
}

