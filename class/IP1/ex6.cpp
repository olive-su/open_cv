#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string  title = "그리기";								// 전역변수 선언
Mat  image;

void onMouse(int event, int x, int y, int flags, void* param)
{
	static Point pt(-1, -1);
	if (event == EVENT_LBUTTONDOWN) {
		if (pt.x < 0) 	pt = Point(x, y);						// 시작좌표 지정
		else {
			rectangle(image, pt, Point(x, y), Scalar(50), 2);	// 종료좌표 및 그리기
			imshow(title, image);
			pt = Point(-1, -1);									// 시작좌표 초기화
		}
	}
	else if (event == EVENT_RBUTTONDOWN) {
		if (pt.x < 0) pt = Point(x, y);
		else {
			Point2d pt2 = pt - Point(x, y);
			int  radius = (int)sqrt(pt2.x * pt2.x + pt2.y * pt2.y);	// 두 좌표간 거리
			circle(image, pt, radius, Scalar(150), 2);

			imshow(title, image);
			pt = Point(-1, -1);
		}
	}
	else if (event == EVENT_MBUTTONDOWN) {
		if (pt.x < 0) pt = Point(x, y);
		else {
			Point pt1(x, y);

			Point2d center = (pt1 + pt) / 2.0;				// 두 좌표 중심
			Size2d  size = (Size2d)((pt1 - pt) / 2.0);		// 두 좌표 차분 – 타원 크기
			size.width = abs(size.width);					// 타원 크기 음수 방지
			size.height = abs(size.height);
			ellipse(image, center, size, 0, 0, 360, Scalar(150), 2);

			imshow(title, image);
			pt = Point(-1, -1);
		}
	}

}

int main()
{
	image = Mat(300, 500, CV_8UC1, Scalar(255));
	imshow(title, image);
	setMouseCallback(title, onMouse, 0);						// 콜백함수 등록

	waitKey(0);
	return 0;
}