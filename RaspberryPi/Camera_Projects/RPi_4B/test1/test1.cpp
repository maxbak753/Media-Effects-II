#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>

// Compile Command: g++ -o test1 test1.cpp `pkg-config --cflags --libs opencv4`

int main() {
    // Command to capture an image using libcamera
    std::string capture_command = "libcamera-jpeg -o capture.jpg --width 1280 --height 720 --nopreview";
    
    while (true) {
        // Run the capture command to take a photo
        int result = std::system(capture_command.c_str());
        if (result != 0) {
            std::cerr << "Error capturing image!" << std::endl;
            return -1;
        }

        // Load the captured image using OpenCV
        cv::Mat image = cv::imread("capture.jpg");
        if (image.empty()) {
            std::cerr << "Failed to load captured image!" << std::endl;
            return -1;
        }

        // Display the image
        cv::imshow("Raspberry Pi Camera", image);

        // Exit if 'q' is pressed
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    cv::destroyAllWindows();
    return 0;
}
