#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include<stdio.h>

using namespace std;
using namespace cv;

int main()
{
	Mat foreground = imread("C:/Users/owner/Desktop/image/Girl_in_front_of_a_green_background.jpg");
	Mat background = imread("C:/Users/owner/Desktop/image/background.jpg");

	resize(background, background, Size(foreground.cols, foreground.rows));

	Mat dst = Mat::zeros(foreground.size(), foreground.type());
	Mat new_image = Mat::zeros(foreground.size(), foreground.type());

	cvtColor(foreground, dst, COLOR_BGR2YCrCb);

	vector<Mat> bgr_planes;
	split(dst, bgr_planes);

	namedWindow("Foreground", 1);
	imshow("Foreground", foreground);

	namedWindow("Background", 1);
	imshow("Background", background);

	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true; 
	bool accumulate = false;

	Mat Cr_hist, Cb_hist;
	int Cr_key = 0; int Cb_key = 0;
	int r_max = 0; int b_max = 0;

	calcHist(&bgr_planes[1], 1, 0, Mat(), Cr_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), Cb_hist, 1, &histSize, &histRange, uniform, accumulate);

	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	normalize(Cr_hist, Cr_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(Cb_hist, Cb_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(Cr_hist.at<float>(i - 1))), Point(bin_w * (i), hist_h - cvRound(Cr_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(Cb_hist.at<float>(i - 1))), Point(bin_w * (i), hist_h - cvRound(Cb_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
	}

	for (int i = 0; i < histSize; i++) {
		if (Cr_hist.at<float>(i) > r_max) {
			r_max = Cr_hist.at<float>(i);
			Cr_key = i;
		}
		if (Cb_hist.at<float>(i) > b_max) {
			b_max = Cb_hist.at<float>(i);
			Cb_key = i;
		}
	}

	namedWindow("calcHist Demo", WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);

	float in_th = 30.0; float out_th = 50.0;
	float d;

	for (int y = 0; y < foreground.rows; y++) {
		for (int x = 0; x < foreground.cols; x++) {
			d = sqrt(pow((dst.at<Vec3b>(y, x)[1] - Cr_key), 2) + pow((dst.at<Vec3b>(y, x)[2] - Cb_key), 2));
			for (int c = 0; c < 3; c++) {
				if (d < in_th) {
					new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(1.0 * background.at<Vec3b>(y, x)[c]);
				}
				else if (d > out_th) {
					new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(1.0 * foreground.at<Vec3b>(y, x)[c]);
				}
				else {
					float alpha = (d - in_th) / (out_th - in_th);
					new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((1 - alpha) * (background.at<Vec3b>(y, x)[c]) + alpha * (foreground.at<Vec3b>(y, x)[c]));
				}
			}
		}
	}

	namedWindow("Chroma Key", 1);
	imshow("Chroma Key", new_image);

	waitKey(0);
	return 0;
}