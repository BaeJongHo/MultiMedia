#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

float Lkernel1[3][3] = { {0, -1, 0},
					   {-1, 4, -1},
				   	   {0, -1, 0} };

float Lkernel2[3][3] = { {-1, -1, -1},
					   {-1, 8, -1},
					   {-1, -1, -1} };

int main(int argc, char** argv)
{
	int n = 3;

	Mat image = imread("C:/Users/owner/Desktop/image/moon_blur.png", IMREAD_GRAYSCALE);
	Mat laplacian = Mat::zeros(image.size(), image.type());
	Mat dst = Mat::zeros(image.size(), image.type());

	double sum1 = 0;
	double c = 1.0;

	//n에 따라 양쪽끝값 설정
	for (int y = (int)(n / 2); y < image.rows - int(n / 2); y++) {
		for (int x = (int)(n / 2); x < image.cols - int(n / 2); x++) {
			//n에 따라 양쪽끝값 설정
			for (int i = -(int)(n / 2); i < (int)n / 2 + 1; i++) {
				for (int j = -(int)(n / 2); j < (int)n / 2 + 1; j++) {
					//2가지 가로, 세로 커널 적용
					sum1 = sum1 + Lkernel1[i + 1][j + 1] * image.at<uchar>(y + i, x + j);
				}
			}
			laplacian.at<uchar>(y, x) = saturate_cast<uchar>(sum1);
			dst.at<uchar>(y, x) = saturate_cast<uchar>(image.at<uchar>(y, x) + c*sum1);
			sum1 = 0;
		}
	}

	namedWindow("Original", 1);
	namedWindow("Laplacian Image", 1);
	namedWindow("Sharpening Image", 1);

	imshow("Original", image);
	imshow("Laplacian Image", laplacian);
	imshow("Sharpening Image", dst);

	waitKey();
	return 0;
}