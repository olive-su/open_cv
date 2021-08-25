#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void drawLineRect() {
	Mat image(300, 400, CV_8UC3, Scalar(255, 255, 255));
	Point pt1(50, 130), pt2(200, 100);
	Rect  rect(pt1, Size(50, 150));

	line(image, pt1, Point(100, 200), Scalar(300, 100, 100));
	line(image, pt2, Point(100, 200), Scalar(100, 100, 100));

	rectangle(image, pt1, pt2, Scalar(255, 0, 255));
	rectangle(image, rect, Scalar(0, 0, 255));

	imshow("직선 & 사각형", image);

	waitKey(0);
}

void drawEllipse() {
	Mat    image = Mat(400, 600, CV_8UC3, Scalar(255, 255, 255));
	Point2d	 center = (Point2d)(image.size() / 2);			// 중심점
	double   c = image.rows / 2, c4 = c / 4;
	Size2d  cir1(c / 2, c / 2);

	ellipse(image, center, cir1, 0, 0, 180, Scalar(255, 0, 0), -1);
	ellipse(image, center, cir1, 0, 180, 360, Scalar(0, 0, 255), -1);

	imshow("반원", image);
	waitKey(0);
}

void main()
{
	drawLineRect();
	drawEllipse();
}