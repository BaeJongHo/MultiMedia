#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char* argv[])
{
	Mat img(256, 256, CV_8U, 255);
	namedWindow("Mat img", WINDOW_AUTOSIZE);
	imshow("Mat img", img);
	waitKey(0);
	return 0;
}