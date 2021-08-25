#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

String title = "conv1";


void addSaltAndPepperNoise(Mat& img, double noise_ratio)
{
	int rows = img.rows;
	int cols = img.cols;
	int ch = img.channels();
	int num_of_noise_pixels = (int)((double)(rows * cols * ch) * noise_ratio);

	for (int i = 0; i < num_of_noise_pixels; i++)
	{
		int r = rand() % rows; 
		int c = rand() % cols; 
		int _ch = rand() % ch;  

		uchar* pixel = img.ptr<uchar>(r) + (c * ch) + _ch;

		*pixel = (rand() % 2 == 1) ? 255 : 0; // black(0) Ȥ�� white(255)�� ��ü
	}
}


int main()
{
	Mat image = imread("images/lena.png", 0);		
	CV_Assert(image.data);								// ���� ���� ����ó��
	// addSaltAndPepperNoise(image, 0.05); 
	//�����ϰ� 0 �Ǵ� 255�� �� ó�� -> �ּ� Ǯ�� ����(������� �� �� �ִ� ��, ����þ� ��� ������ �� �ΰ��� ���� �ҽ��� ũ�� ������ ��ġ�� ����)

	
	Mat avg_img, blur_img, box_img, gauss_img;
	Size  size(5, 5);

	Mat mask(5, 5, CV_32F, 1 / 25.0f);

	filter2D(image, avg_img, -1, mask);
	blur(image, blur_img, size);						// OpenCV ���� ���� �Լ�
	boxFilter(image, box_img, -1, size);				// OpenCV ���� �ڽ� ���� �Լ�
	GaussianBlur(image, gauss_img, size, 1.5);


	float data[] = {									// ������ ����ũ ���� ����
		-1, -1, -1,
		-1, 9, -1,
		-1, -1, -1,
	};

	Mat sharpen1;
	Mat sharpenmask(3, 3, CV_32F, data);
	filter2D(image, sharpen1, -1, sharpenmask);

	Mat medianFilteredImg;
	medianBlur(image, medianFilteredImg, 3);

	imshow("title", image);
	imshow("avg_img", avg_img);
	imshow("blur_img", blur_img);
	imshow("box_img", box_img);
	imshow("gauss_img", gauss_img);

	imshow("sharpen1", sharpen1);

	imshow("medianFilteredImg", medianFilteredImg);

	waitKey();
	return 0;
}