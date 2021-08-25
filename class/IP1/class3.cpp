#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;

void main()
{
	Mat image = imread("images\\road_3.jpg", -1); // -1 : unchanged

	//bgr
	// -> hls
	Mat cvtimg;
	cvtColor(image, cvtimg, CV_BGR2HLS);

	Mat split_img[3];
	split(cvtimg, split_img);
	Mat split_img_bgr[3];
	split(cvtimg, split_img_bgr);


	imshow("bgr", image);
	imshow("hls", cvtimg);
	imshow("hls_h", split_img[0]);
	imshow("bgr_r", split_img_bgr[2]);

	waitKey(0);
}