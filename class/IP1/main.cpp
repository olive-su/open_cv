#include "opencv2/highgui.hpp"		// highgui opencv 제공하는 gui 기능을 사용하려고 include

using namespace cv;		// opencv 네임스페이스 생략
void main()
{
	/*
	Mat 클래스 -> 영상, 행렬값(행렬값을 갖고있는 자료형은 전부다 Mat을 사용함) -> 행렬값이 결국 화면에 표시되는 값이다.
	Mat 객체 변수명 image
	(rows(수직방향 수), cols(수평방향 수), type(8u, 8s, 16 + 채널수), 초기값)
	*/

	// Mat  image(300, 400, CV_8UC1, cv::Scalar(222)); // grayscale
	Mat  image(300, 400, CV_8UC3, cv::Scalar(0, 255, 255)); // color BGR(순서가 BGR임!)
	imshow("영상보기", image); // image Mat 객체를 화면에 새창으로 띄움(title)
	waitKey(0); // 사용자의 키 입력 대기 함수


}