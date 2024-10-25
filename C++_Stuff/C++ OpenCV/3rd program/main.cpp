#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem> // Include this header

int main(int argc, char** argv ) {
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    cv::Mat image = cv::imread("C:/Users/maxba/Documents/C++_Stuff/C++ OpenCV/3rd program/build/DrCostanza.JPEG");
    std::cout << "Hello, from opencv_test!\n";

    if ( !image.data ) {
        printf("No image data \n");
        return -1;
    }
    
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    cv::waitKey(0);
    return 0;
}


// #include <iostream>
// #include <opencv2/opencv.hpp>

// int main(int argc, char** argv ) {
//     cv::Mat image = cv::imread("C:/Users/maxba/Documents/C++_Stuff/C++ OpenCV/3rd program/build/DrCostanza.JPEG");
//     std::cout << "Hello, from opencv_test!\n";

//     if ( !image.data )
//     {
//         printf("No image data \n");
//         return -1;
//     }
//     cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
//     imshow("Display Image", image);
//     cv::waitKey(0);
//     return 0;
// }



// #include <stdio.h>
// #include <opencv2/opencv.hpp>

// using namespace cv;
// int main(int argc, char** argv )
// {

//     Mat image;
//     image = imread("C:/Users/maxba/Desktop/TEST/build/lenna.png");
//     if ( !image.data )
//     {
//         printf("No image data \n");
//         return -1;
//     }
//     namedWindow("Display Image", WINDOW_AUTOSIZE );
//     imshow("Display Image", image);
//     waitKey(0);
//     return 0;
// }