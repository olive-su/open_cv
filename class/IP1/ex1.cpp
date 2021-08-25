#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void exPoint() {
	cout << endl << endl << "POINT Ŭ���� ==========>" << endl;
	// POINT Ŭ����
	Point2d pt1(20, 20);
	Point2d pt2(50, 70);
	Point2d pt3(70, 100); /* x, y ��ǥ (double ��) - ���� ���󿡼��� �Ҽ����� ������ ���⶧���� �ݿø��ؼ� ��ǥ���� ã�ư��Ե� */

	// Vector Ŭ����
	vector <Point2d> pts;
	pts.push_back(pt1);
	pts.push_back(pt2);
	pts.push_back(pt3);

	for (int i = 0; i < (int)pts.size(); i++) {
		cout << format("pts[%d] = ", i) << pts[i] << endl;
		cout << format("pts[%d] = ", i) << pts[i].x << "," << pts[i].y << endl;
	}

	cout << endl << endl;

	// ����
	Point2d pt4 = pt1 + pt2;
	cout << pt4.x << "," << pt4.y << endl;

	Point2d pt5 = pt1 * 3;
	cout << pt5.x << "," << pt5.y << endl;	// ������ ������.x, ������.y�� ����
}

void exRect() {
	cout << endl << endl << "RECT Ŭ���� ==========>" << endl;
	// rect int
	Rect2i rect(Point2i(30, 40), Size2i(100, 200));
	cout << "rect = " << rect << endl;

	rect += Point2i(10, 10);	// x30, y40 -> 40, 50
	rect += Size2i(20, 30);		//x100, h200 - > 120, 230
	cout << "rect = " << rect << endl;

	// rect float
	Rect2f rectf(Point2f(30.1f, 40.1f), Size2f(100.1f, 200.1f));
	cout << "rectf = " << rectf << endl;

	rectf += Point2f(10.1f, 10.1f);
	rectf += Size2f(20.1f, 30.1f);
	cout << "rectf = " << rectf << endl;

	// rect double
	Rect2d rectd(Point2d(30.00001, 40.00001), Size2d(100.00001, 200.00001));
	cout << "rectf = " << rectf << endl;

	rectd += Point2d(10.00001, 10.00001);
	rectd += Size2d(20.00001, 30.00001);
	cout << "rectd = " << rectd << endl;
}

void exScalar() {
	cout << endl << endl << "Scalar Ŭ���� ==========>" << endl;
	
	Scalar sc_num_int(10, 20, 30);	// �ּ� 1������ �ּ� 4������
	cout << sc_num_int << endl;

	Scalar sc_num_db(10.01, 20.02, 30.03);
	cout << sc_num_db << endl;
}


void exBasicMat() {
	cout << endl << endl << "BasicMat ==========>" << endl;

	float data[] = {
		1.5f, 2.f, 3  , 4  ,  5,
		6   , 7.f, 8.f, 9  , 1.1f,
		11  , 12 , 13 ,14  , 15,
		16  , 17 , 18 ,19  , 20
	};

	// Mat ��ü�� �����ϴ� ���
	//Mat m1(4, 5, CV_32F, data);
	Mat m1(4, 5, CV_8U, data);

	cout << m1 << endl;
}

void exMatRect() {
	cout << endl << endl << "exMatRect ==========>" << endl;

	Mat m(10, 15, CV_8U, Scalar(0));

	Rect rect1(5, 3, 5, 4);
	Rect rect2(10, 5, 4, 3);
	m(rect1).setTo(500);	// ROI(Region of image)
	m(rect2).setTo(300);

	cout << m << endl;

	imshow("���󺸱�", m);
	waitKey(0);
}

void exRotRect() {
	cout << endl << endl << "exRotRect ==========>" << endl;
	
	Point2f ptCenter(10.1f, 10.2f);
	Size size(5, 5);
	RotatedRect rt1(ptCenter, size, 135.0f);

	cout << rt1.center << "," << rt1.angle  << endl;
}


void main()
{
	exPoint();	// Point Ŭ���� Ȱ�� ����(��ǥ ����, Size Ŭ����)
	exRect();	// Rect Ŭ���� Ȱ�� ����
	exScalar();	// �迭�� ó���ϴ� Ŭ����
	exBasicMat();	//
	exMatRect();
	exRotRect();
}