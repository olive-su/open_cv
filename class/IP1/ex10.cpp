#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void roi_sum_mean() {
	Mat image = imread("images/logo.jpg", IMREAD_COLOR);
	Rect roi(50, 50, 150, 200);

	Mat roi_img = image(roi);
	Scalar avg = mean(roi_img);
	Scalar sum;
	for (int i = 0; i < roi_img.rows; i++) {
		for (int j = 0; j < roi_img.cols; j++) {
			sum += (Scalar)roi_img.at<Vec3b>(i, j);
		}
	}
	sum /= (int)roi_img.total();

	rectangle(image, roi, Scalar(0, 0, 255), 2);
	cout << "OpenCV 사용: " << avg << endl;
	cout << "직접 순회  : " << sum << endl << endl;

	imshow("image", image);
	waitKey(0);
}


void matAt() {
	Mat  m1(3, 5, CV_32SC1);
	Mat  m2(3, 5, CV_32FC1);
	Mat  m3(3, 5, CV_8UC2);
	Mat  m4(3, 5, CV_32SC3);

	for (int i = 0; i < m1.rows; i++) {
		for (int j = 0; j < m1.cols; j++)
		{
			m1.at<int>(i, j) = i;
			Point pt(j, i);
			m2.at<float>(pt) = (float)j;

			int idx[2] = { i, j };
			m3.at<Vec2b>(idx) = Vec2b(0, 1);

			m4.at<Vec3i>(i, j)[0] = 0;
			m4.at<Vec3i>(i, j)[1] = 1;
			m4.at<Vec3i>(i, j)[2] = 2;
		}
	}
	cout << "[m1] = " << endl << m1 << endl;
	cout << "[m2] = " << endl << m2 << endl;
	cout << "[m3] = " << endl << m3 << endl;
	cout << "[m4] = " << endl << m4 << endl;
}

void matPtr() {
	Mat  m1(3, 5, CV_8UC1);
	Mat  m2(m1.size(), CV_32FC1);

	for (int i = 0; i < m1.rows; i++)
	{
		uchar* ptr_m1 = m1.ptr(i);
		float* ptr_m2 = m2.ptr<float>(i);
		for (int j = 0; j < m1.cols; j++)
		{
			ptr_m1[j] = j;
			*(ptr_m2 + j) = (float)j;
		}
	}
	cout << "m1 = " << endl << m1 << endl << endl;
	cout << "m2 = " << endl << m2 << endl;
}


void imgAt() {
	Mat image = imread("images\\logo.jpg", IMREAD_GRAYSCALE);
	Mat atImage(image.size(), image.type());
	atImage.setTo(0);


	clock_t begin = clock();

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++)
		{
			atImage.at<uchar>(i, j) = 255-image.at<uchar>(i, j);
			//atImage.at<uchar>(i, j) = saturate_cast<uchar>(image.at<uchar>(i, j) + 50);
		}
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << elapsed_secs << endl;

	imshow("image_at_1", image);
	imshow("image_at_2", atImage);
	waitKey();
	destroyAllWindows();
}

void imgPtr() {
	Mat image = imread("images\\logo.jpg", IMREAD_GRAYSCALE);
	Mat atImage(image.size(), image.type());
	atImage.setTo(0);

	clock_t begin = clock();

	for (int i = 0; i < image.rows; i++)
	{
		uchar* ptr_src = image.ptr(i);
		uchar* ptr_dst = atImage.ptr(i);
		for (int j = 0; j < image.cols; j++)
		{
			ptr_dst[j] = 255 - ptr_src[j];
		}
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << elapsed_secs << endl;

	imshow("image_ptr_1", image);
	imshow("image_ptr_2", atImage);
	waitKey();
	destroyAllWindows();
}

void imgIter() {
	Mat image = imread("images\\logo.jpg");

	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();

	clock_t begin = clock();

	for (; it != itend; it += 1)
	{
		(*it)[0] = (*it)[0] - 100;
		(*it)[1] = (*it)[1] - 100;
		(*it)[2] = (*it)[2] - 100;

	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << elapsed_secs << endl;

	imshow("image_iter", image);
	waitKey();
	destroyAllWindows();
}

int main()
{
	roi_sum_mean();

	cout << "matAt-------------------------------\n\n";
	matAt();
	cout << "matPtr-------------------------------\n\n";
	matPtr();


	cout << "imgAt-------------------------------\n\n";
	imgAt();
	cout << "imgPtr-------------------------------\n\n";
	imgPtr();

	cout << "imgIter-------------------------------\n\n";
	imgIter();
	return 0;
}