#include <iostream>
#include <opencv2/opencv.hpp>
#define PI 3.1415

using namespace cv;
using namespace std;

void rgb2hsi(Mat& RGB_image, Mat& HSI_image);

int main()
{
	Mat image = imread("C:/Users/owner/Desktop/image/lena_noise.png");
	Mat dst = Mat::zeros(image.size(), image.type());

	rgb2hsi(image, dst);

	waitKey();
	return 0;
}

void rgb2hsi(Mat& RGB_image, Mat& HSI_image) {
	vector<Mat> RGB_image_components, HSI_image_components;
	for (int i = 0; i < 3; i++) {
		HSI_image_components.push_back(Mat(RGB_image.size(), CV_8UC1));
	}
	split(RGB_image, RGB_image_components);

	for (int i = 0; i < RGB_image.rows; i++) {
		for (int j = 0; j < RGB_image.cols; j++) {
			float r = RGB_image_components[2].at<uchar>(i, j);
			float g = RGB_image_components[1].at<uchar>(i, j);
			float b = RGB_image_components[0].at<uchar>(i, j);
			float hue, saturation, intensity, min_val;

			intensity = (r + g + b) / (3.0);
			min_val = min(r, min(g, b));

			if (intensity > 0.0)
				saturation = 1 - (min_val / intensity);
			if (saturation < 0.00001) {
				saturation = 0;
			}
			else if (saturation > 0.99999) {
				saturation = 1;
			}

			if (saturation > 0) {
				hue = (0.5 * ((r - g) + (r - b))) / sqrt(((r - g) * (r - g)) + ((r - b) * (g - b)));
				hue = acos(hue);
				if (b > g) {
					hue = ((360 * PI) / 180.0) - hue;
				}
			}
			else {
				hue = 0;
			}
			HSI_image_components[2].at<uchar>(i, j) = intensity;
			HSI_image_components[1].at<uchar>(i, j) = saturation * 100;
			HSI_image_components[0].at<uchar>(i, j) = (hue * 180) / PI;
		}
	}
	merge(HSI_image_components, HSI_image);

	namedWindow("Original", 1);
	namedWindow("HSI image", 1);

	imshow("Original", RGB_image);
	imshow("HSI image", HSI_image);
}