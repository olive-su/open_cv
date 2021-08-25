#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void loadConvert() {

	Mat image = imread("images/logo.jpg", IMREAD_UNCHANGED); // IMREAD_GRAYSCALE
	CV_Assert(image.data);										// 영상파일 예외 처리

	vector<int> params_jpg;
	params_jpg.push_back(IMWRITE_JPEG_QUALITY);		// JPG 화질 설정
	params_jpg.push_back(100);

	vector<int> params_jpg_2;
	params_jpg_2.push_back(IMWRITE_JPEG_QUALITY);		// JPG 화질 설정
	params_jpg_2.push_back(1);

	vector<int> params_png;
	params_png.push_back(IMWRITE_PNG_COMPRESSION);// PNG 압축레벨 설정
	params_png.push_back(0);

	vector<int> params_png_2;
	params_png_2.push_back(IMWRITE_PNG_COMPRESSION);// PNG 압축레벨 설정
	params_png_2.push_back(9);

	imwrite("images/logo_conv1.jpg", image, params_jpg);		// 지정화질로 저장
	imwrite("images/logo_conv2.jpg", image, params_jpg_2);		// 지정화질로 저장
	imwrite("images/logo_conv1.png", image, params_png);
	imwrite("images/logo_conv2.png", image, params_png_2);

	imshow("변환", image);
	waitKey();
}

int main()
{
	loadConvert();
	return 0;
}