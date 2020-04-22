#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;


int main(int argc, char** argv)
{
    double alpha=0.5;
    double beta;

    Mat src1 = imread("C:/Users/owner/Desktop/image/Lena_color.png");
    Mat src2 = imread("C:/Users/owner/Desktop/image/coffee.jpg");

    cv::resize(src1, src1, cv::Size(src2.cols,src2.rows),0,0,INTER_NEAREST);

    Mat dst = Mat::zeros( src1.size(), src1.type() );

    std::cout << "alpha " ; std::cin >> alpha;
    beta = 1.0;

    // Do the operation new_image(i,j) = alpha*image(i,j) + beta
    for( int y = 0; y < src1.rows; y++ ) {
        for( int x = 0; x < src1.cols; x++ ) {
            for( int c = 0; c < 3; c++ ) {
                dst.at<Vec3b>( y, x )[c] = saturate_cast<uchar>( alpha*( src1.at<Vec3b>( y, x )[c] )
                                                                      + alpha*( src2.at<Vec3b>( y, x )[c] )  );
            }
        }
    }

    namedWindow( "Linear Blend", 1 );

    beta = (1.0-alpha);
	
    //addWeighted(src1, alpha, src2, beta, 0.0, dst);
    imshow( "Linear Blend", dst );

    waitKey();
    return 0;
}