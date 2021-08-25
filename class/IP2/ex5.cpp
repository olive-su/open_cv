#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Range th1(50, 100), th2(100, 200);								// 트랙바로 선택할 범위 변수
Mat hue, light;													// 색상, 밝기 채널 전역 변수지정

Mat bgr[3];
int thb = 50, thg = 50, thr = 50;								// 트랙바로 선택할 범위 변수

String title = "이진화";

void onThreshold(int  value, void* userdata)					// 시작 범위 트랙바 콜백 함수
{
	Mat result = Mat(hue.size(), CV_8U, Scalar(0));

	// 선택 범위에 이진화 수행
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++)
		{
			// 선택 범위에 대한 조건 설정
			bool ck1 = hue.at<uchar>(i, j) >= th1.start && hue.at<uchar>(i, j) < th1.end;
			bool ck2 = light.at<uchar>(i, j) >= th2.start && light.at<uchar>(i, j) < th2.end;

			result.at<uchar>(i, j) = (ck1 && ck2) ? 255 : 0;		// 이진값 지정
		}
	}
	imshow(title, result);
}

void hsl() {
	Mat image = imread("images/biglogo.jpg", IMREAD_COLOR);// 컬러 영상 로드
	CV_Assert(image.data);

	Mat HSV, hsv[3];
	cvtColor(image, HSV, CV_BGR2HLS);			// 컬러 공간 변환
	split(HSV, hsv);										// 채널 분리
	hsv[0].copyTo(hue);										// hue 행렬에 색상 채널 복사
	hsv[1].copyTo(light);										// light 행렬에 색상 채널 복사

	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar("Hue_th1", title, &th1.start, 180, onThreshold);	// 트랙바 등록
	createTrackbar("Hue_th2", title, &th1.end, 180, onThreshold);
	createTrackbar("light_th1", title, &th2.start, 256, onThreshold);
	createTrackbar("light_th2", title, &th2.end, 256, onThreshold);

	onThreshold(0, 0);											// 이진화 수행
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
	Mat image = imread("images/biglogo.jpg", IMREAD_COLOR);// 컬러 영상 로드
	CV_Assert(image.data);

	split(image, bgr);

	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar("B_th", title, &thb, 256, th);	// 트랙바 등록
	createTrackbar("G_th", title, &thg, 256, th);
	createTrackbar("R_th", title, &thr, 256, th);

	th(0,0);											// 이진화 수행
	imshow("image", image);
	waitKey(0);
}

int main()
{
	hsl();
	rgb();
	return 0;
}