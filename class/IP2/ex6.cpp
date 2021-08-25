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

		*pixel = (rand() % 2 == 1) ? 255 : 0; // black(0) 혹은 white(255)로 교체
	}
}


int main()
{
	Mat image = imread("images/lena.png", 0);		
	CV_Assert(image.data);								// 영상 파일 예외처리
	// addSaltAndPepperNoise(image, 0.05); 
	//랜덤하게 0 또는 255의 점 처리 -> 주석 풀고 실행(결과에서 알 수 있는 점, 가우시안 결과 봤을때 한 두개의 정보 소실이 크게 영향을 미치지 않음)

	
	Mat avg_img, blur_img, box_img, gauss_img;
	Size  size(5, 5);

	Mat mask(5, 5, CV_32F, 1 / 25.0f);

	filter2D(image, avg_img, -1, mask);
	blur(image, blur_img, size);						// OpenCV 제공 블러링 함수
	boxFilter(image, box_img, -1, size);				// OpenCV 제공 박스 필터 함수
	GaussianBlur(image, gauss_img, size, 1.5);


	float data[] = {									// 사프닝 마스크 원소 지정
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