// First Program For Fun (imagination experiment)
// Maxwell Bakalos 10/10/2024

#include <iostream>             // Input-Output Stream
#include <opencv2/opencv.hpp>   // Open Computer Vision
#include <filesystem>           // print working directory
#include <cmath>                // pow() exponents
#include <chrono>               // elapsed time
// #include <thread>               // pause
// #include <matplot/matplot.h>    // MatPlot++

// #ifndef M_PI
// #define M_PI 3.14159265358979323846
// #endif

using namespace cv;
using namespace std;

// Functions

// Main
int main(int argc, char** argv ) {
    int dims[2] = {50, 400};
    cv::Mat field = cv::Mat::zeros(dims[0], dims[1], CV_8U);

    // Display the matrix
    // std::cout << "Matrix filled with zeros:\n" << field << std::endl;

    float position[2] = {static_cast<float>(dims[0]/2), static_cast<float>(dims[1]/2)};
    float proposed_position[2] = {0,0};
    float direction[2] = {2,3};
    int disp_count = 0;
    // bool proposed_position_invalid;

    int v_i = static_cast<int>(max(direction[0], direction[1])); // direction interval for a whole number as smallest x-y component
    float v[2] = {direction[0] / v_i, direction[1] / v_i}; // normalized velocity vector where the largest interval component is 1 unit

    // imshow("Field", field);
    cv::namedWindow("Field", cv::WINDOW_NORMAL);
    cv::resizeWindow("Field", 4*dims[1], 4*dims[0]);

    for (int i=0; i < 500; ++i) {
        // field.at<uchar>(position[0], position[1]) = 0; // clear old position brightness
        // fade brightness
        field *= 0.9;

        proposed_position[0] = position[0] + v[0];
        proposed_position[1] = position[1] + v[1];

        // If it will be out of bounds, reverse the direction (bounce)

        bool bound_flag[2] = {((proposed_position[0] <= 0) || (proposed_position[0] >= dims[0])), ((proposed_position[1] <= 0) || (proposed_position[1] >= dims[1]))};

        if (bound_flag[0] && bound_flag[1]) {
            v[0] *= -1; v[1] *= -1;
            proposed_position[0] = position[0] + v[0];
            proposed_position[1] = position[1] + v[1];
            // cout << "BOUND FLAG: " << bound_flag[0] << " " << bound_flag[1] << endl;
            // cout << "Corner!" << endl;
        }
        else if (bound_flag[0]) {
            v[0] *= -1;
            proposed_position[0] = position[0] + v[0];
            proposed_position[1] = proposed_position[1];
            // cout << "BOUND FLAG: " << bound_flag[0] << " " << bound_flag[1] << endl;
            // cout << "0 Bound" << endl;
        }
        else if (bound_flag[1]) {
            v[1] *= -1;
            proposed_position[0] = proposed_position[0];
            proposed_position[1] = position[1] + v[1];
            // cout << "BOUND FLAG: " << bound_flag[0] << " " << bound_flag[1] << endl;
            // cout << "1 Bound" << endl;
        }

        position[0] = proposed_position[0]; position[1] = proposed_position[1];
        // cout << ".";

        field.at<uchar>(std::round(position[0]), std::round(position[1])) = 255; // make new position bright

        if (disp_count >= 1) {
            cv::imshow("Field", field);
            cv::waitKey(1);
            disp_count = 0;
        }
        disp_count += 1;
    }

    cout << "{*}~ THE END ~{*}" << endl;

    // Keep the final result displayed until a key is pressed
    cv::waitKey(0);
    return 0;
    
}