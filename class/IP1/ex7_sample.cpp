// 카메라 연결하는 부분
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

VideoCapture capture;

// 문자열 출력 함수 - 그림자 효과 
void put_string(Mat& frame, string text, Point pt, int value)
{
	text += to_string(value);
	Point shade = pt + Point(2, 2);
	int font = FONT_HERSHEY_SIMPLEX;
	putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);		// 그림자 효과 	
	putText(frame, text, pt, font, 0.7, Scalar(120, 200, 90), 2);// 작성 문자
}

void zoom_bar(int value, void*) { 							// 콜백함수
	capture.set(CAP_PROP_ZOOM, value);					
}
void focus_bar(int value, void*) {
	capture.set(CAP_PROP_FOCUS, value);					
}
void bright_bar(int value, void*) {
	capture.set(CAP_PROP_BRIGHTNESS, value);				
}
void contrast_bar(int value, void*) {
	capture.set(CAP_PROP_CONTRAST, value);					
}
int main()
{
	capture.open(0);											// 0번 카메라 연결
	CV_Assert(capture.isOpened());								// 카메라 연결 예외 처리

	capture.set(CAP_PROP_FRAME_WIDTH, 400); 					// 카메라 프레임 너비
	capture.set(CAP_PROP_FRAME_HEIGHT, 300);
	capture.set(CAP_PROP_AUTOFOCUS, 0);							// 오토포커싱 중지
	capture.set(CAP_PROP_BRIGHTNESS, 150);						// 프레임 밝기 초기화

	int zoom = capture.get(CAP_PROP_ZOOM);						// 카메라 속성 가져오기
	int focus = capture.get(CAP_PROP_FOCUS);
	int bright = capture.get(CAP_PROP_BRIGHTNESS);
	int contrast = capture.get(CAP_PROP_CONTRAST);

	string title = "카메라 연결 및 제어";							// 윈도우 이름 지정
	namedWindow(title);											
	createTrackbar("zoom", title, &zoom, 10, zoom_bar); 		
	createTrackbar("focus", title, &focus, 40, focus_bar);
	createTrackbar("bright", title, &bright, 255, bright_bar);
	createTrackbar("contrast", title, &contrast, 40, contrast_bar);

	while(true) {
		Mat frame;
		capture >> frame;										// 카메라 영상 가져오기

		put_string(frame, "zoom: ", Point(10, 240), zoom);			// 글자그리기
		put_string(frame, "focus: ", Point(10, 270), focus);		// 글자그리기

		put_string(frame, "bright: ", Point(200, 240), bright);		// 글자그리기
		put_string(frame, "contrast: ", Point(200, 270), contrast);	// 글자그리기

		imshow(title, frame);
		if (waitKey(30) >= 0) break; // 아무버튼이나 
	}
	return 0;
}