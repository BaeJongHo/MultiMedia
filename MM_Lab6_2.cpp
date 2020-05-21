#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Point2f inputQuad[4];
	Point2f outputQuad[4];
	Mat warp_mat(3, 3, CV_32FC1);
	Mat src, dst;

	src = imread("C:/Users/owner/Desktop/image/Lena_color.png");
	dst = Mat::zeros(src.rows, src.cols, src.type());

	inputQuad[0] = Point2f(-30, -60);
	inputQuad[1] = Point2f(src.cols + 50, -50);
	inputQuad[2] = Point2f(src.cols + 100, src.rows + 50);
	inputQuad[3] = Point2f(-50, src.rows + 50);

	outputQuad[0] = Point2f(0, 0);
	outputQuad[1] = Point2f(src.cols - 1, 0);
	outputQuad[2] = Point2f(src.cols - 1, src.rows - 1);
	outputQuad[3] = Point2f(0, src.rows -1);
	
	warp_mat = getPerspectiveTransform(inputQuad, outputQuad);
	warpPerspective(src, dst, warp_mat, dst.size());

	namedWindow("Original Image", 1);
	imshow("Original Image", src);

	namedWindow("Perspective Transformation", 1);
	imshow("Perspective Transformation", dst);

	waitKey();
	return 0;
}