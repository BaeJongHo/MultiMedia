#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char** argv)
{
	double alpha; /**< Simple contrast control */
	int beta; /**< Simple brightness control */

	std::cout << "alpha, beta 입력: ";
	std::cin >> alpha >> beta;

	Mat image = imread("C:/Users/owner/Desktop/image/background.jpg");
	Mat new_image = Mat::zeros(image.size(), image.type());

	/// Initialize values

	/// Do the operation new_image(i,j) = alpha*image(i,j) + beta
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha * (image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	/// Create Windows
	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	/// Show stuff
	imshow("Original Image", image);
	imshow("New Image", new_image);

	/// Wait until user press some key
	waitKey();
	return 0;
}