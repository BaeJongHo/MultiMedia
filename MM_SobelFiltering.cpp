#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int gx[3][3] = { {1, 0, -1},
				 {2, 0, -2},
				 {1, 0, -1} };

int gy[3][3] = { {1, 2, 1},
				 {0, 0, 0},
				 {-1, -2, -1} };

int main(int argc, char** argv)
{
	int n = 3;

	Mat image = imread("C:/Users/owner/Desktop/image/Lena_color.png", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(image.size(), image.type());

	double sumX = 0;
	double sumY = 0;
	double G = 0;

	//n에 따라 양쪽끝값 설정
	for (int y = (int)(n / 2); y < image.rows - int(n / 2); y++) {
		for (int x = (int)(n / 2); x < image.cols - int(n / 2); x++) {

			//n에 따라 양쪽끝값 설정
			for (int i = -(int)(n / 2); i < (int)n / 2 + 1; i++) {
				for (int j = -(int)(n / 2); j < (int)n / 2 + 1; j++) {
					//2가지 가로, 세로 커널 적용
					sumX = sumX + gx[i + 1][j + 1] * image.at<uchar>(y + i, x + j);
					sumY = sumY + gy[i + 1][j + 1] * image.at<uchar>(y + i, x + j);
				}
			}

			//G값 구하기
			G = pow(sumX, 2) + pow(sumY, 2);
			G = sqrt(G);

			dst.at<uchar>(y, x) = G;
			G = 0;
			sumX = 0;
			sumY = 0;
		}
	}

	namedWindow("Original", 1);
	namedWindow("Sobel Filter", 1);

	imshow("Original", image);
	imshow("Sobel Filter", dst);

	waitKey();
	return 0;
}