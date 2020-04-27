#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	int n = 3;
	int med[9];

	Mat image = imread("C:/Users/owner/Desktop/image/lena_noise.png");
	Mat dst = Mat::zeros(image.size(), image.type());

	//n에 따라 양쪽끝값 설정
	for (int y = (int)(n / 2); y < image.rows - int(n / 2); y++) {
		for (int x = (int)(n / 2); x < image.cols - int(n / 2); x++) {
			//n에 따라 양쪽끝값 설정
			for (int c = 0; c < 3; c++) {
				int k = 0;
				for (int i = -(int)(n / 2); i < (int)n / 2 + 1; i++) {
					for (int j = -(int)(n / 2); j < (int)n / 2 + 1; j++) {
						med[k] = image.at<Vec3b>(y + i, x + j)[c];
						k++;
					}
				}
				sort(med, med + 9);
				dst.at<Vec3b>(y, x)[c] = med[4];
			}
		}
	}

	namedWindow("Original", 1);
	namedWindow("Median Filtering", 1);

	imshow("Original", image);
	imshow("Median Filtering", dst);

	waitKey();
	return 0;
}