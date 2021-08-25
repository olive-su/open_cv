#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

void draw_houghLines(Mat image, Mat& dst, vector<Vec2f> lines, int nline)
{
	cvtColor(image, dst, COLOR_GRAY2BGR);
	for (int i = 0; i < min((int)lines.size(), nline); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		double a = cos(theta), b = sin(theta);

		Point2d delta(1000 * -b, 1000 * a);
		Point2d pt(a * rho, b * rho);

		line(dst, pt + delta, pt - delta, Scalar(0, 0, 255), 1, LINE_AA);
	}
}

void max_object(Mat img, Rect& rect)
{
	vector<vector<Point>> contours;
	findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);	// 외곽선 검출해주는 함수

	int max_area = 0;
	for (int i = 0; i < (int)contours.size(); i++)	// 가장 큰 영역 가져오기
	{
		Rect r = boundingRect(contours[i]);			// 외곽선 영역 포함 사각형
		if (max_area < r.area()) {
			max_area = r.area();
			rect = r;
		}
	}
	rect = rect - Point(10, 10) + Size(20, 20);
}

void main()
{
	Rect  rect;
	Mat		gray, canny, morph, th_gray, canny_line, dst;
	double rho = 1, theta = CV_PI / 180;				// 허프변환 거리간격, 각도간격
	vector<Vec2f> lines;								// 허프 검출 라인들

	Mat image = imread("images\\test_hough.png", IMREAD_COLOR);
	CV_Assert(image.data);

	cvtColor(image, gray, CV_BGR2GRAY);						// 명암도 영상 변환
	threshold(gray, th_gray, 240, 255, THRESH_BINARY);		//이진 영상 변환
	erode(th_gray, morph, Mat(), Point(-1, -1), 2);			// 침식 연산

	max_object(morph, rect);								// 가장 큰 객체 검색
	rectangle(morph, rect, Scalar(100), 2);					// 검색 객체 표시

	Canny(th_gray(rect), canny, 40, 100);
	HoughLines(canny, lines, rho, theta, 50);
	draw_houghLines(canny, canny_line, lines, 1);

	double angle = lines[0][1] * (180 / CV_PI);
	cout << angle << "," << lines[0][1] << endl;
	Point  center = image.size() / 2;
	Mat rot_map = getRotationMatrix2D(center, angle, 1);

	warpAffine(image, dst, rot_map, image.size(), INTER_LINEAR);
	imshow("morph", morph);
	imshow("image", image);
	imshow("canny", canny);
	imshow("th_gray(rect)", th_gray(rect));
	imshow("houghline", canny_line);
	imshow("dst", dst);

	resizeWindow("line", 150, 150);
	waitKey();
}