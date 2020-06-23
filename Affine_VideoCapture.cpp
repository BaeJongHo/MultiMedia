#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

void myAffine(Mat src, Mat warp_dst);

int main(int, char**)
{
	VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;

	Mat edges;
	namedWindow("Affine transform", 1);
	for (;;) {
		Mat frame;
		cap >> frame;
		myAffine(frame, frame);
		imshow("Affine transform", frame);
		if (waitKey(30) >= 0)
			break;
	}

	return 0;
}

void myAffine(Mat src, Mat warp_dst) {
	Point2f srcTri[3];
	Point2f dstTri[3];

	Mat warp_mat(2, 3, CV_32FC1);
	
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);

	dstTri[0] = Point2f(src.cols * 0.0, src.rows * 0.33);
	dstTri[1] = Point2f(src.cols * 0.85, src.rows * 0.25);
	dstTri[2] = Point2f(src.cols * 0.15, src.rows * 0.7);

	warp_mat = getAffineTransform(srcTri, dstTri);
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());
}