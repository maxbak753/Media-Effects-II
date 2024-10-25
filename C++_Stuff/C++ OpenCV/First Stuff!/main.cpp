#include <opencv2/opencv.hpp>
#include <iostream>

// https://youtu.be/CnXUTG9XYGI?si=ir_vr6KLd8ymPoZQ

int main() {
    std::string imagePath = "DrCostanza.JPEG";
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
    cv::imshow("Display Window!!!", image);
    cv::waitKey(0);

    return 0;
}