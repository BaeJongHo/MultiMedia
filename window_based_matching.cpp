#include <opencv2/core.hpp> 
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>

using namespace cv;
using namespace std;

int main()
{
	Mat img0, img1, map;
	img0 = imread("C:/Users/owner/Desktop/image/scene1.row3.col2.png");
	img1 = imread("C:/Users/owner/Desktop/image/scene1.row3.col3.png");
	cvtColor(img0, img0, COLOR_BGR2GRAY);
	cvtColor(img1, img1, COLOR_BGR2GRAY);

	namedWindow("Left", 1);
	namedWindow("Right", 1);
	namedWindow("Disparity Map", 1);

	map = Mat::zeros(img0.rows, img0.cols, img0.type());

	float sum = 0, min = -1;
	int disparity;
		
	for (int i = 0; i < img0.rows - 5; i++) {
		for (int j = 0; j < img0.cols - 5; j++) {
			for (int pass = 0; pass < img0.cols - 5 - j; pass++) {
				if (pass > 25)
					break;

				for (int s = 0; s < 5; s++) {
					for (int t = 0; t < 5; t++) {
				 		sum += abs(img1.at<uchar>(i + s, j + t) - img0.at<uchar>(i + s, j + t + pass));
					}
				}
				sum /= 25;
				if (min == -1) {
			 		min = sum;
					disparity = pass;
				}
			 	if (min > sum) {
					min = sum;
					disparity = pass;
				}
			}
			sum = 0;
			min = -1;
			map.at<uchar>(i, j) = saturate_cast<uchar>(20 * disparity);
		}
	}

	imshow("Left", img0);
	imshow("Right", img1);
	imshow("Disparity Map", map);
	waitKey(0);

	return 0;
}