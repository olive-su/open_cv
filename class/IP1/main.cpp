#include "opencv2/highgui.hpp"		// highgui opencv �����ϴ� gui ����� ����Ϸ��� include

using namespace cv;		// opencv ���ӽ����̽� ����
void main()
{
	/*
	Mat Ŭ���� -> ����, ��İ�(��İ��� �����ִ� �ڷ����� ���δ� Mat�� �����) -> ��İ��� �ᱹ ȭ�鿡 ǥ�õǴ� ���̴�.
	Mat ��ü ������ image
	(rows(�������� ��), cols(������� ��), type(8u, 8s, 16 + ä�μ�), �ʱⰪ)
	*/

	// Mat  image(300, 400, CV_8UC1, cv::Scalar(222)); // grayscale
	Mat  image(300, 400, CV_8UC3, cv::Scalar(0, 255, 255)); // color BGR(������ BGR��!)
	imshow("���󺸱�", image); // image Mat ��ü�� ȭ�鿡 ��â���� ���(title)
	waitKey(0); // ������� Ű �Է� ��� �Լ�


}