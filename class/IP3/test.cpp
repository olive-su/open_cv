#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
using namespace std;

void main()
{
	Mat image = imread("images\\test_hough.png", IMREAD_COLOR);
	CV_Assert(image.data);

	Mat resized, resized_ratio;

	//resize
	resize(image, resized, Size(100, 100), 0, 0, INTER_LINEAR); // 2*2 참조, INTER_LINEAR, 4*4 INTER_CUBIC
	resize(image, resized_ratio, Size(0, 0), 0.3, 0.5, INTER_LINEAR); // 비율로 처리

	// flip
	Mat resized_ratio_flip;
	flip(resized_ratio, resized_ratio_flip, -1); // -1: 반전 x축 , y축 반전, 0: 반전 x축 반전, 1:반전 y축 반전

	// rotate
	Mat resized_ratio_rotate;
	rotate(resized_ratio, resized_ratio_rotate, ROTATE_90_CLOCKWISE);

	// affine 평행을 유지 한체 변환
	//getAffineTransform() : src 3좌표와 dst 3좌표의 변환행렬을 반환
	//getRotationMatrix2D() : 중심점과 크기변경을 수행할 수 있는 행렬을 반환
	Mat affine_rot = getRotationMatrix2D(Point(20, 20), -30, 0.5);
	Mat affine_rot_res;
	cout << affine_rot << endl << endl;
	warpAffine(image, affine_rot_res, affine_rot, image.size());

	circle(image, Point(20, 20), 5, Scalar(0, 0, 255), 1);

	// 점 대응
	Point2f srcPts[3], dstPts[3];
	srcPts[0] = Point2f(10, 10);
	srcPts[1] = Point2f(400, 100);
	srcPts[2] = Point2f(100, 200);
	dstPts[0] = Point2f(30, 30);
	dstPts[1] = Point2f(500, 200);
	dstPts[2] = Point2f(200, 300);

	Mat affine_trans = getAffineTransform(srcPts, dstPts);
	Mat affine_trans_res;
	cout << affine_trans << endl << endl;
	warpAffine(image, affine_trans_res, affine_trans, image.size());
	circle(image, srcPts[0], 5, Scalar(0, 0, 255), -1);
	circle(image, srcPts[1], 5, Scalar(0, 255, 0), -1);
	circle(image, srcPts[2], 5, Scalar(255, 0, 0), -1);

	// perpective
	image = imread("images\\drive_2.png", IMREAD_COLOR);
	CV_Assert(image.data);

	Point2f src_pers[4], dst_pers[4];
	src_pers[0] = Point2f(654, 350), src_pers[1] = Point2f(715, 350);
	src_pers[2] = Point2f(380, 560), src_pers[3] = Point2f(992, 560);

	dst_pers[0] = Point2f(380, 0), dst_pers[1] = Point2f(992, 0);
	dst_pers[2] = Point2f(380, 560), dst_pers[3] = Point2f(992, 560);

	Mat pers_trans = getPerspectiveTransform(src_pers, dst_pers);
	Mat pers_trans_res;
	warpPerspective(image, pers_trans_res, pers_trans, image.size(), INTER_CUBIC);

	circle(image, src_pers[0], 5, Scalar(0, 255, 255), -1);
	circle(image, src_pers[1], 5, Scalar(0, 255, 0), -1);
	circle(image, src_pers[2], 5, Scalar(255, 255, 0), -1);
	circle(image, src_pers[3], 5, Scalar(255, 0, 0), -1);

	// 차선추출
	Mat algo_1_split[3];
	Mat algo_1_r_th;
	split(pers_trans_res, algo_1_split);
	boxFilter(algo_1_split[2], algo_1_split[2], -1, Size(31, 31));
	threshold(algo_1_split[2], algo_1_r_th, 140, 255, THRESH_BINARY);

	Mat algo_1_r_th_noise_filter;
	Mat kernel_morp(11, 11, CV_8UC1, Scalar(1));
	morphologyEx(algo_1_r_th, algo_1_r_th_noise_filter, MORPH_ERODE, kernel_morp);
	morphologyEx(algo_1_r_th_noise_filter, algo_1_r_th_noise_filter, MORPH_DILATE, kernel_morp);


	Mat display;
	cvtColor(algo_1_r_th_noise_filter, display, COLOR_GRAY2BGR);
	Rect rect_window(0, 0, 50, 30);
	rectangle(display, rect_window, Scalar(255, 0, 0), 1);

	Mat window_map = algo_1_r_th_noise_filter.clone();
	Mat window_map_display = algo_1_r_th_noise_filter.clone();
	window_map.setTo(0);
	window_map_display.setTo(0);

	// 영역별 평균계산
	for (int i = 0; i < algo_1_r_th_noise_filter.cols - rect_window.width; i += rect_window.width) {
		for (int j = 0; j < algo_1_r_th_noise_filter.rows - rect_window.height; j += rect_window.height) {
			rect_window.x = i;
			rect_window.y = j;
			Scalar meanvalue = mean(algo_1_r_th_noise_filter(rect_window));
			if (meanvalue[0] < 100) {
				window_map(rect_window).setTo(0);
			}
			else {
				window_map(rect_window).setTo(meanvalue[0]);
			}
			window_map_display(rect_window).setTo(mean(algo_1_r_th_noise_filter(rect_window)));
			rectangle(window_map_display, rect_window, Scalar(255), 1);
		}
	}

	// 계획된 차선 그리기
	dst_pers[2] = Point2f(380, 560), dst_pers[3] = Point2f(992, 560);
	line(display, dst_pers[0], dst_pers[2], Scalar(0, 0, 255), 1);
	line(display, dst_pers[1], dst_pers[3], Scalar(0, 0, 255), 1);
	line(display, (dst_pers[0] + dst_pers[1]) / 2, (dst_pers[2] + dst_pers[3]) / 2, Scalar(255, 0, 0), 1);


	// 절반씩 영역 선택
	Rect rect_left(0, 0, (dst_pers[0].x + dst_pers[1].x) / 2, 30);
	Rect rect_right((dst_pers[0].x + dst_pers[1].x) / 2, 0, (dst_pers[0].x + dst_pers[1].x) / 2, 30);
	rectangle(display, rect_left, Scalar(0, 255, 255), 1);
	rectangle(display, rect_right, Scalar(255, 255, 0), 1);


	// 제일 높은지점(두께가 있는) 영역 검색 
	for (int j = 0; j < algo_1_r_th_noise_filter.rows - rect_window.height; j += rect_window.height) {
		int top_value_left = 0;
		int top_value_right = 0;
		// 왼쪽
		for (int i = 0; i < algo_1_r_th_noise_filter.cols - rect_window.width; i += rect_window.width) {
			rect_window.x = i;
			rect_window.y = j;
			Scalar meanvalue = mean(window_map(rect_window));
			if (i < (dst_pers[0].x + dst_pers[1].x) / 2) {
				if (top_value_left < meanvalue[0]) {
					top_value_left = meanvalue[0];
				}
			}
			else {
				if (top_value_right < meanvalue[0]) {
					top_value_right = meanvalue[0];
				}
			}
		}
		for (int i = 0; i < algo_1_r_th_noise_filter.cols - rect_window.width; i += rect_window.width) {
			rect_window.x = i;
			rect_window.y = j;
			Scalar meanvalue = mean(window_map(rect_window));
			if (i < (dst_pers[0].x + dst_pers[1].x) / 2) {
				if (top_value_left > meanvalue[0]) {
					window_map(rect_window).setTo(0);
				}
			}
			else {
				if (top_value_right > meanvalue[0]) {
					window_map(rect_window).setTo(0);
				}
			}
		}
	}

	// 내부색칠 (원본이미지에 매핑)
	for (int j = rect_window.height; j < algo_1_r_th_noise_filter.rows - rect_window.height; j++) {
		int first_value_left = 0;
		int last_value_right = 0;
		// 왼쪽
		for (int i = 0; i < algo_1_r_th_noise_filter.cols - rect_window.width; i++) {
			if (i >= (dst_pers[0].x + dst_pers[1].x) / 2) {
				break;
			}
			if (window_map.at<uchar>(j, i) > 0)
			{
				first_value_left = i;
				break;
			}
		}
		for (int i = algo_1_r_th_noise_filter.cols - rect_window.width; i > 0; i--) {
			if (i <= (dst_pers[0].x + dst_pers[1].x) / 2) {
				break;
			}
			if (window_map.at<uchar>(j, i) > 0)
			{
				last_value_right = i;
				break;
			}
		}
		if (first_value_left == 0 || last_value_right == 0) {
			line(window_map, Point(0, j), Point(algo_1_r_th_noise_filter.cols, j), Scalar(0), 1);
		}
		else {
			line(window_map, Point(first_value_left, j), Point(last_value_right, j), Scalar(255), 1);
		}
	}

	// 복원
	Mat pers_trans_reverse = getPerspectiveTransform(dst_pers, src_pers);
	Mat pers_trans_reverse_res;
	warpPerspective(window_map, pers_trans_reverse_res, pers_trans_reverse, image.size(), INTER_CUBIC);

	imshow("image_ori", image);
	// 색칠
	add(image, Scalar(0, 0, 255), image, pers_trans_reverse_res);

	//namedWindow("custom", WINDOW_NORMAL);
	imshow("image", image);
	imshow("dst", pers_trans_res);
	imshow("algo_1_r_th_noise_filter", algo_1_r_th_noise_filter);
	imshow("window_map", window_map);
	imshow("window_map_display", window_map_display);
	imshow("pers_trans_reverse_res", pers_trans_reverse_res);
	imshow("display", display);
	waitKey();
}