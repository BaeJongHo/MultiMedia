#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
using namespace cv;

int main() {
	float scale_X, scale_Y;
	Mat src, dst, new_image;

	printf("X scale : ");
	cin >> scale_X;

	printf("Y scale : ");
	cin >> scale_Y;

	src = imread("C:/Users/owner/Desktop/image/Lena_color.png");
	cvtColor(src, dst, COLOR_BGR2RGB);
	dst = Mat::zeros(src.rows * scale_Y, src.cols * scale_X, src.type());
	resize(src, new_image, Size(), scale_X, scale_Y, INTER_LINEAR);

	for (int y = 0; y < dst.rows; y++) {
		for (int x = 0; x < dst.cols; x++) {
			int px = floor(x / scale_X);
			int py = floor(y / scale_Y);

			double fx1 = (double)x / (double)scale_X - (double)px;
			double fx2 = 1 - fx1;

			double fy1 = (double)y / (double)scale_Y - (double)py;
			double fy2 = 1 - fy1;

			double w1 = fx2 * fy2;
			double w2 = fx1 * fy2;
			double w3 = fx2 * fy1;
			double w4 = fx1 * fy1;

			if (px == src.cols - 1)
				px--;
			if (py == src.rows - 1)
				py--;

			Vec3b P1 = src.at<Vec3b>(py, px);
			Vec3b P2 = src.at<Vec3b>(py, px + 1);
			Vec3b P3 = src.at<Vec3b>(py + 1, px);
			Vec3b P4 = src.at<Vec3b>(py + 1, px + 1);

			dst.at<Vec3b>(y, x) = w1 * P1 + w2 * P2 + w3 * P3 + w4 * P4;
		}
	}

	namedWindow("Original", 1);
	imshow("Original", src);

	namedWindow("Bilinear Image", 1);
	imshow("Bilinear Image", dst);

	namedWindow("Method Image", 1);
	imshow("Method Image", new_image);

	waitKey(0);
	return 0;
}