#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // GStreamer pipeline to capture video from the Raspberry Pi Camera using libcamera
    std::string pipeline = "libcamerasrc ! video/x-raw, width=160, height=120, framerate=10/1 ! videoconvert ! appsink";

    // Open the camera using the GStreamer pipeline
    cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);

    // Check if the camera is opened
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera!" << std::endl;
        return -1;
    }

    // Create a window to display the video
    cv::namedWindow("Camera", cv::WINDOW_NORMAL);

    // Variables to hold frame data
    cv::Mat frame;

    while (true) {
        // Grab the next frame from the camera
        cap >> frame;

        // Check if the frame is empty
        if (frame.empty()) {
            std::cerr << "Error: Empty frame!" << std::endl;
            break;
        }

        // Display the frame
        cv::imshow("Camera", frame);

        // Wait for key press and exit if 'q' is pressed
        char c = (char)cv::waitKey(1);
        if (c == 'q') {
            break;
        }
    }

    // Release the camera and close the window
    cap.release();
    cv::destroyAllWindows();

    return 0;
}