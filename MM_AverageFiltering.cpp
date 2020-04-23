#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	//n값 홀수로 입력
	int n;
	printf("N값을 홀수로 입력하시오: ");
	scanf("%d", &n);

	Mat image = imread("C:/Users/owner/Desktop/image/lena_noise.png", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(image.size(), image.type());

	double sum = 0;
	double average = 0;

	//n에 따라 양쪽끝값 설정
	for (int y = (int)(n / 2); y < image.rows - int(n / 2); y++) {
		for (int x = (int)(n / 2); x < image.cols - int(n / 2); x++) {

			//n에 따라 양쪽끝값 설정
			for (int i = -(int)(n / 2); i < (int)n / 2 + 1; i++) {
				for (int j = -(int)(n / 2); j < (int)n / 2 + 1; j++) {
					sum = sum + image.at<uchar>(y + i, x + j);
				}
			}

			//평균구하기
			average = sum / ((double)n * double(n));
			
			dst.at<uchar>(y, x) = average;
			average = 0;
			sum = 0;
		}
	}

	namedWindow("Original", 1);
	namedWindow("Average", 1);

	imshow("Original", image);
	imshow("Average", dst);

	waitKey();
	return 0;
}