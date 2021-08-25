#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

uchar bilinear_value(Mat img, double x, double y)
{
	if (x >= img.cols - 1)  x--;
	if (y >= img.rows - 1)  y--;

	// 4개 화소 결정
	Point pt((int)x, (int)y);
	int A = img.at<uchar>(pt);
	int B = img.at<uchar>(pt + Point(0, 1));
	int C = img.at<uchar>(pt + Point(1, 0));
	int D = img.at<uchar>(pt + Point(1, 1));

	//1차 보간
	double alpha = y - pt.y;
	double beta = x - pt.x;
	int M1 = A + (int)cvRound(alpha * (B - A));
	int M2 = C + (int)cvRound(alpha * (D - C));

	//2차 보간
	int P = M1 + (int)cvRound(beta * (M2 - M1));
	return  saturate_cast<uchar>(P);
}


void affine_transform(Mat img, Mat& dst, Mat map, Size size)
{
	dst = Mat(img.size(), img.type(), Scalar(0));
	Rect rect(Point(0, 0), img.size());

	Mat  inv_map;
	invertAffineTransform(map, inv_map);

	for (int i = 0; i < size.height; i++) {
		for (int j = 0; j < size.width; j++)
		{
			Point3d ji(j, i, 1);
			Mat   xy = inv_map * (Mat)ji;
			Point2d pt = (Point2d)xy;

			if (rect.contains(pt))
				dst.at<uchar>(i, j) = bilinear_value(img, pt.x, pt.y);
		}
	}
}

Mat  getAffineMap(Point2d center, double dgree, double fx = 1, double fy = 1,
	Point2d translate = Point(0, 0))
{
	Mat rot_map = Mat::eye(3, 3, CV_64F);
	Mat center_trans = Mat::eye(3, 3, CV_64F);
	Mat org_trans = Mat::eye(3, 3, CV_64F);
	Mat scale_map = Mat::eye(3, 3, CV_64F);
	Mat trans_map = Mat::eye(3, 3, CV_64F);

	double radian = dgree / 180 * CV_PI;
	rot_map.at<double>(0, 0) = cos(radian);
	rot_map.at<double>(0, 1) = sin(radian);
	rot_map.at<double>(1, 0) = -sin(radian);
	rot_map.at<double>(1, 1) = cos(radian);

	center_trans.at<double>(0, 2) = center.x;
	center_trans.at<double>(1, 2) = center.y;
	org_trans.at<double>(0, 2) = -center.x;
	org_trans.at<double>(1, 2) = -center.y;

	scale_map.at<double>(0, 0) = fx;
	scale_map.at<double>(1, 1) = fy;
	trans_map.at<double>(0, 2) = translate.x;
	trans_map.at<double>(1, 2) = translate.y;

	Mat ret_map = center_trans * rot_map * trans_map * scale_map * org_trans;

	ret_map.resize(2);
	return ret_map;
}


void affine() {

	Mat image = imread("images\\road_2.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Point center = image.size() / 2, tr(100, 0);
	double  angle = 30.0;
	Mat dst1, dst2, dst3, dst4;

	Mat aff_map1 = getAffineMap(center, angle);
	Mat aff_map2 = getAffineMap(Point2d(0, 0), 0, 2.0, 1.5);
	Mat aff_map3 = getAffineMap(center, angle, 0.7, 0.7);
	Mat aff_map4 = getAffineMap(center, angle, 0.7, 0.7, tr);

	warpAffine(image, dst1, aff_map1, image.size());
	warpAffine(image, dst2, aff_map2, image.size());
	affine_transform(image, dst3, aff_map3, image.size());
	affine_transform(image, dst4, aff_map4, image.size());

	imshow("image", image);
	imshow("dst1-회전만", dst1);
	imshow("dst2-크기변경만", dst2);
	imshow("dst3-회전+크기변경", dst3);
	imshow("dst4-회전+크기변경+평행이동", dst4);

	waitKey();
}


void perspective() {
	Mat image = imread("images\\road_2.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Point2f pts1[4] = {
		Point2f(90, 170) , Point2f(300, 120),
		Point2f(90, 285), Point2f(300, 320)
	};
	Point2f pts2[4] = {
		Point2f(60, 120), Point2f(340, 110),
		Point2f(60, 280), Point2f(340, 280)
	};

	Mat dst(image.size(), CV_8UC1);
	Mat perspect_map = getPerspectiveTransform(pts1, pts2);
	warpPerspective(image, dst, perspect_map, image.size(), INTER_CUBIC);



	vector<Point3f> pts3, pts4;
	for (int i = 0; i < 4; i++) {
		pts3.push_back(Point3f(pts1[i].x, pts1[i].y, 1));
	}
	transform(pts3, pts4, perspect_map);
	cout << "[perspect_map] = " << endl << perspect_map << endl << endl;

	for (int i = 0; i < 4; i++)
	{
		pts4[i] /= pts4[i].z;
		cout << "pts2[" << i << "]=" << pts2[i] << "\t";
		cout << "pts4[" << i << "]=" << pts4[i] << endl;

		circle(image, pts1[i], 2, Scalar(0, 0, 255), 2);
		circle(dst, pts2[i], 2, Scalar(0, 0, 255), 2);
	}

	imshow("image ", image);
	imshow("dst - 왜곡 보정", dst);
	waitKey();
}

int main()
{
	cout << "affine-------------------------------\n\n";
	affine();
	cout << "perspective-------------------------------\n\n";
	perspective();
	return 0;
}