#include "opencv2/highgui.hpp"   
#include <opencv2/opencv.hpp>  
// highgui opencv 제공하는 gui 기능을 사용하려고 include 

using namespace cv;  // opencv 네임스페이스 생략

Mat image = imread("images\\sign_1.jpg", IMREAD_COLOR);

#include <iostream>
using namespace std;

// 콜백함수 정의
void onMouse(int event, int x, int y, int flags, void* param)
{            // 마우스클릭이벤트, 마우스 위치, 키보드, userData) 
	if (x > 0 && y > 0
		&& x < image.size().width
		&& y < image.size().height) {
		cout << image.at<Vec3b>(x, y) << endl;
	}
}

void main()
{
	Mat res = image.clone();
	res.setTo(Scalar(0, 0, 0));


	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++)
		{
			if (image.at<Vec3b>(i, j)[0] < 50
				&& image.at<Vec3b>(i, j)[1] < 50
				&& image.at<Vec3b>(i, j)[2] > 200)
			{
				res.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}


	// opencv 내부 메서드 사용
	// threshold // - 값기준으로 0, maxval
	// inrange  // - min < x < max

	Mat split_mat[3];
	split(image, split_mat);

	// b/ g /r

	Mat res_tmp;
	Mat res_mask;

	threshold(split_mat[0], res_tmp, 50, 255, THRESH_BINARY_INV);
	res_tmp.copyTo(res_mask);
	res_tmp.setTo(0);
	threshold(split_mat[1], res_tmp, 50, 255, THRESH_BINARY_INV);
	bitwise_and(res_mask, res_tmp, res_mask);
	res_tmp.setTo(0);
	threshold(split_mat[2], res_tmp, 200, 255, THRESH_BINARY);
	bitwise_and(res_mask, res_tmp, res_mask);

	Mat res_color = image.clone();
	res_color.setTo(Scalar(0, 0, 0));
	Mat red_mat = image.clone();
	red_mat.setTo(Scalar(0, 0, 255));
	red_mat.copyTo(res_color, res_mask);

	imshow("res", res);
	imshow("image", image);
	imshow("res_mask", res_mask);
	imshow("res_color", res_color);
	waitKey(0);

}