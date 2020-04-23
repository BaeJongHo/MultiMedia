#define _CRT_SECURE_NO_WARNINGS
#define PI 3.1415
#include <opencv2/opencv.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace cv;
using namespace std;

double** gm;
void gausian();
double sig;
int n;

int main(int argc, char** argv)
{
	//Input N as odds number
	printf("N값을 홀수로 입력하시오: ");
	scanf("%d", &n);

	//Input Sigma
	printf("시그마 값을 입력하시오: ");
	scanf("%lf", &sig);

	//Create Gausian Matrix memory
	gm = (double**)malloc(sizeof(double*) * n);
	for (int i = 0; i < n; i++)
		gm[i] = (double*)malloc(sizeof(double) * n);

	Mat image = imread("C:/Users/owner/Desktop/image/lena_noise.png", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(image.size(), image.type());

	gausian();

	for (int y = (int)(n / 2); y < image.rows - (int)(n / 2); y++) {
		for (int x = (int)(n / 2); x < image.cols - (int)(n / 2); x++) {
			for (int i = -(int)(n / 2); i < (int)n / 2 + 1; i++) {
				for (int j = -(int)(n / 2); j < (int)n / 2 + 1; j++) {
					dst.at<uchar>(y, x) += saturate_cast<uchar>(gm[j + (int)(n / 2)][i + (int)(n / 2)] * image.at<uchar>(y + i, x + j));
				}
			}
		}
	}
	
	namedWindow("Original", 1);
	namedWindow("Gausian", 1);

	imshow("Original", image);
	imshow("Gausian", dst);

	waitKey();
	return 0;
}

//Create Gausian Matrix with N
void gausian()
{
	double r;
	double s = 2 * sig * sig;
	double sum = 0.0;
	for (int x = -(int)(n/2); x <= (int)(n / 2); x++)
	{
		for (int y = -(int)(n / 2); y <= (int)(n / 2); y++)
		{
			r = sqrt(x * x + y * y);
			gm[x + (int)(n / 2)][y + (int)(n / 2)] = (exp(-(r * r) / s)) / (PI * s);
			sum += gm[x + (int)(n / 2)][y + (int)(n / 2)];
		}
	}
	
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			gm[i][j] /= sum;

	printf("\nGausian Matrix\n");
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%.4f ", gm[i][j]);
		}
		printf("\n");
	}
}