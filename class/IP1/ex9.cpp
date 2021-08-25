#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void def_mat() {
	cout << endl << endl << "def_mat" << endl;
	// elementwise
	// 선언방식
	Matx23f m1(1, 2, 3, 1, 2, 3);
	Matx23f m2(3, 3, 4, 2, 2, 3);
	Mat m3 = (Mat)(m1 + m2);
	Mat m4 = (Mat)(m1 * m2.t());

	cout << "[m1] = " << endl << m1 << endl;
	cout << "[m2] = " << endl << m2 << endl;
	cout << "[m3] = " << endl << m3 << endl;
	cout << "[m2_transpose] = " << endl << m2.t() << endl;
	cout << "[m4] = " << endl << m4 << endl;

	// 1 2 3    3 2   3 + 6 + 12    2 + 4 + 9
	// 1 2 3    3 2
	//          4 3

	////////////////////////////////////////////////////

	// 영상 24bit, BGR
	uchar data[] = {
		1, 2, 3, 4, 5, 6, 
		7, 8, 9, 10, 11, 12
	};
	Mat m5(2, 3, CV_8UC2, data);
	vector<Mat> sp_mat;

	split(m5, sp_mat); // split 함수
	cout << "[m5] = " << endl << sp_mat[1] << endl;
}

void reduce_mat() {
	cout << endl << endl << "reduce_mat" << endl;
	Mat_<uchar> m1(2, 3), m2(2, 3); // 8U, uchar 8S

	m1 << 1, 1, 2, 2, 3, 3;
	m2 << 2, 1, 3, 1, 4, 1;

	Mat m3, m4;

	subtract(m1, m2, m3);

	cout << "[m1] = " << endl << m1 << endl;
	cout << "[m2] = " << endl << m2 << endl;
	cout << "[m3] = " << endl << m3 << endl;

	reduce(m1, m4, 0, REDUCE_MAX); // REDUCE_SUM, REDUCE_AVG 최대값 축소 수직방향(dim = 0) 수평(1)
	cout << "[m4] = " << endl << m4 << endl;
	cout << "sum(m1) = " << sum(m1) << endl;
	cout << "mean(m2) = " << mean(m2) << endl;
}


void colorSplit() {
	Mat image = imread("images/logo.jpg", IMREAD_COLOR);
	Mat bgr[3], blue_img, red_img, green_img;
	Mat zero(image.size(), CV_8U, Scalar(0));
	
	split(image, bgr);

	Mat b_ch[] = { bgr[0], zero, zero };
	Mat g_ch[] = { zero, bgr[1], zero };
	Mat r_ch[] = { zero, zero ,  bgr[2] };

	merge(b_ch, 3, blue_img);
	merge(g_ch, 3, green_img);
	merge(r_ch, 3, red_img);

	imshow("image", image);
	imshow("blue_img", blue_img);
	imshow("green_img", green_img);
	imshow("red_img", red_img);
	imshow("b", bgr[0]);
	imshow("g", bgr[1]);
	imshow("r", bgr[2]);
	waitKey();
	destroyAllWindows();
}

void main() {
	def_mat();
	reduce_mat();
	colorSplit();
}