#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	double fx, fy;
	cin >> fx >> fy;
	Mat src = imread("C:/Users/owner/Desktop/image/Lena_color.png");
	Mat result = Mat::zeros(src.rows * fy, src.cols * fx, src.type());
	Mat dst = Mat::zeros(src.rows, src.cols, src.type());

	resize(src, dst, Size(), 1.5, 1.5, INTER_NEAREST);

	for (int y = 0; y < result.rows; y++) {
		for (int x = 0; x < result.cols; x++) {
			int px = floor(x / fx);
			int py = floor(y / fy);
			for (int c = 0; c < 3; c++) {
				result.at<Vec3b>(y, x)[c] = src.at<Vec3b>(py, px)[c];
			}
		}
	}

	namedWindow("Original Image", 1);
	imshow("Original Image", src);

	namedWindow("Result", 1);
	imshow("Result", result);

	namedWindow("Method", 1);
	imshow("Method", dst);

	waitKey();
	return 0;
}