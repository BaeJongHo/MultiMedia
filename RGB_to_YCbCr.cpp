#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

double alpha; // contrast control
int beta;  // brightness control

int main()
{
	Mat src = imread("C:/Users/owner/Desktop/image/Lena_color.png");
	Mat dst = Mat::zeros(src.size(), src.type());
	Mat new_image = Mat::zeros(src.size(), src.type());

	std::cout << "Enter the alpha value [0.0-2.0]: "; std::cin >> alpha;
	//std::cout << "Enter the beta value [0-100]: "; std::cin >> beta;

	namedWindow("Original Image", 1);
	imshow("Original Image", src);

	// Processing in RGB color model
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha * (src.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	namedWindow("New Image in RGB", 1);
	imshow("New Image in RGB", new_image);

	// Processing in YCbCr
	cvtColor(src, dst, COLOR_BGR2YCrCb);
	for (int y = 0; y < dst.rows; y++) {
		for (int x = 0; x < dst.cols; x++) {
			dst.at<Vec3b>(y, x)[0] = saturate_cast<uchar>(alpha * (dst.at<Vec3b>(y, x)[0]) + beta);
		}
	}
	cvtColor(dst, new_image, COLOR_YCrCb2BGR);

	namedWindow("New Image in YCbCr", 1);
	imshow("New Image in YCbCr", new_image);


	// Processing in HSV
	cvtColor(src, dst, COLOR_BGR2HSV);
	for (int y = 0; y < dst.rows; y++) {
		for (int x = 0; x < dst.cols; x++) {
			dst.at<Vec3b>(y, x)[2] = saturate_cast<uchar>(alpha * (dst.at<Vec3b>(y, x)[2]) + beta);
		}
	}
	cvtColor(dst, new_image, COLOR_HSV2BGR);

	namedWindow("New Image in HSV", 1);
	imshow("New Image in HSV", new_image);

	waitKey(0);
	return 0;
}