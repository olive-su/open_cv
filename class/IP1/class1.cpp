#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>


using namespace cv;

Mat image; // 지역변수 -> 다른함수 사용 불가

// 콜백 함수 정의
void onMouse(int event, int x, int y, int flags, void* param) 
// 함수 파라미터는 opencv 자체에 규정되어 있어서 파라미터는 동일하게 넘겨줘야함
{			// 마우스 클릭 이벤트, 마우스 위치, 키보드, userData
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

	image = imread("images\\logo.jpg", IMREAD_UNCHANGED); // 해당 이미지를 grayscale로 읽음
	/*
	color = bgr채널 (3채널의 합으로 표현)
	grayscale = 1채널 (1채널의 세기로 표현) 0~255, 0 검은색 - 255 흰색
	*/


	Mat mask(image.size().height, image.size().width, CV_8UC3); // image와 동일한 크기의 mask를 만들기 위해 사이즈 지정
	// mask(w, h, 0~255)

	mask.setTo(0); // 초기화 -> 이 해당 행렬에 대해서 특정 값으로 치환


	Rect rect_area(10, 10, 100, 150);

	rectangle(mask, rect_area, Scalar(0, 0, 255), -1); // -1을 하면 안이 채워진 사각형 띄움

	// 얕은복사, 깊은복사

	// clipping (rect변수, mask)
	// 얕은 복사 -> 서브 매트릭스(Region of image)
	Mat clip = image(rect_area);
	// = image 변수에 해당하는 행렬을 내가 참조하겠다 (rect_area 영역만큼)
	// 서브매트릭스, 주의 -! 서브매트릭스에 선을 그리면, image에도 선이 그려진다.

	// 깊은 복사
	Mat clip_deepcopy = image(rect_area).clone(); // 새로운 메모리를 만들어서(mat) 반환

	// 논리연산 (마스크에 있는 영역을 추출해올 수 있음)
	Mat bitwise_mask(image.size().height, image.size().width, CV_8UC3);
	bitwise_and(image, mask, bitwise_mask);

	// Error) image(3채널) != mask(1채널)
	// image 3채널, 3채널, 결과



	imshow("myimage", image);
	imshow("mymask", mask);
	imshow("myclip", clip);
	imshow("bitwise_mask", bitwise_mask);

	setMouseCallback("myimage", onMouse, 0);
	int value = 50; // 초기값
	createTrackbar("컬러변경", "myimage", &value, 255, onChange);


	waitKey(0); // delay - ex.33ms -> 30FPS (초당 프레임 계속 가져오기. 괄호 내의 값은 영상에 따라 알아서!)

	return 0;
}