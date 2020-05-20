#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Point2f srcTri[3];
	Point2f dstTri[3];
	Mat warp_mat(2, 3, CV_32FC1);
	Mat src, warp_dst;

	src = imread("C:/Users/owner/Desktop/image/background.jpg");
	warp_dst = Mat::zeros(src.rows, src.cols, src.type());

	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);

	dstTri[0] = Point2f(src.cols * 0.0, src.rows * 0.33);
	dstTri[1] = Point2f(src.cols * 0.85, src.rows * 0.25);
	dstTri[2] = Point2f(src.cols * 0.15, src.rows * 0.7);

	warp_mat = getAffineTransform(srcTri, dstTri);
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());

	namedWindow("Original Image", 1);
	imshow("Original Image", src);

	namedWindow("Affine Transformation", 1);
	imshow("Affine Transformation", warp_dst);

	waitKey();
	return 0;
}