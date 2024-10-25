// #include <iostream>
// #include <opencv2/opencv.hpp>

// // https://youtu.be/CnXUTG9XYGI?si=ir_vr6KLd8ymPoZQ

// int main() {
//     std::string imagePath = "DrCostanza.JPEG";
//     cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
//     cv::imshow("Display Window!!!", image);
//     cv::waitKey(0);

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem> // Include this header

int main(int argc, char** argv ) {
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    std::string imagePath = "DrCostanza.JPEG";
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
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