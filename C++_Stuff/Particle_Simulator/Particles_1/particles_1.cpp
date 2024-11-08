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

// // Classes
// class particle {
//   public:
//     float ax = 0.0; // acceleration (gravity) in x-direction
//     float ay = 0.3; // acceleration (gravity) in y-direction
//     float tx = 0; // time for x-gravity
//     float ty = 0; // time for y-gravity
//     bool position_invalid; // true if the position is invalid (out-of-bounds)
//     float bounce_loss = 0.9; // bounce loss (% of velocity to keep after bounce)
//     float air_res = 0.9999; // air resistance (% of velocity kept throughout time)
//     float fric = 0.99; // friction (% of velocity kept while touching the walls)
//     float dp[2]; // Δp = change in position

//     particle(string choice) {
//         if (choice == "frictionless") {
//             bounce_loss = 0;
//             air_res = 0;
//             fric = 0;
//         }
//     }
//     particle(float gx, float gy) {
//         ax = gx;
//         ay = gy;
//     }
// };

// Main
int main(int argc, char** argv ) {
    cout << " /--- - - -      - - - ---\\" << endl;
    cout << "{*}~ PARTICLE SIMULATOR ~{*}" << endl;
    cout << " \\--- - - -      - - - ---/" << endl;
    cout << "" << endl;
    cout << "  hold ESC or 'q' to exit   " << endl;

    int dims[2] = {50, 100};
    cv::Mat field = cv::Mat::zeros(dims[0], dims[1], CV_8U);

    // Display the matrix
    // std::cout << "Matrix filled with zeros:\n" << field << std::endl;

    float position[2] = {static_cast<float>(dims[0]/2), static_cast<float>(dims[1]/2)};
    float proposed_position[2] = {0,0};
    float direction[2] = {3,1};
    int disp_count = 0;
    // bool proposed_position_invalid;

    int v_i = static_cast<int>(max(direction[0], direction[1])); // direction interval for a whole number as smallest x-y component
    float v[2] = {direction[0] / v_i, direction[1] / v_i}; // normalized velocity vector where the largest interval component is 1 unit
    float v_scale = 5;
    v[0] *= v_scale; v[1] *= v_scale; // scale velocity (spped-up / slow-down)

    // imshow("Particle Simulation", field);
    cv::namedWindow("Particle Simulation", cv::WINDOW_NORMAL);
    cv::resizeWindow("Particle Simulation", 6*dims[1], 6*dims[0]);
    int display_interval = 7; // after how many iterations does a new frame of the simulation appear


    int secs_timeout = 60; // seconds after which the window closes
    // Record the start time
    auto start = std::chrono::steady_clock::now();

    

    float ax = 0.000; // acceleration (gravity) in x-direction
    float ay = 0.003; // acceleration (gravity) in y-direction
    float tx = 0;
    float ty = 0;
    bool position_invalid;
    int pos_inv_count = 0;

    float bounce_loss = 0.9; // bounce loss (% of velocity to keep after bounce)
    float air_res = 0.9999; // air resistance (% of velocity kept throughout time)
    float fric = 0.99; // friction (% of velocity kept while touching the walls)

    float dp[2];

    int iw = 0;

    // wall_collisions(direction, velocity, secs_timeout)

    while (true) {
        iw += 1;
        // field.at<uchar>(position[0], position[1]) = 0; // clear old position brightness
        // fade brightness
        field *= 0.9;

        // calculate new proposed position
        dp[0] = v[0] + (ay*ty); dp[1] = v[1] + (ax*tx);
        proposed_position[0] = position[0] + dp[0];
        proposed_position[1] = position[1] + dp[1];

        // If it will be out of bounds, reverse the direction (bounce)
        position_invalid = 1;
        while (position_invalid) {
            bool bound_flag[2] = {((proposed_position[0] < 0) || (proposed_position[0] >= dims[0])), ((proposed_position[1] < 0) || (proposed_position[1] >= dims[1]))};
            pos_inv_count += 1;

            if (bound_flag[0] && bound_flag[1]) {
                tx = 0; ty = 0; // reset time for gravity (x & y)
                v[0] *= -bounce_loss; v[1] *= -bounce_loss;
            }
            else if (bound_flag[0]) {
                ty = 0;
                v[0] *= -bounce_loss;
            }
            else if (bound_flag[1]) {
                tx = 0;
                v[1] *= -bounce_loss;
            }
            else {
                position_invalid = 0;
                pos_inv_count = 0;
                tx += 1;
                ty += 1;
                break;
            }

            // calculate new proposed position
            dp[0] = v[0] + (ay*ty); dp[1] = v[1] + (ax*tx);
            proposed_position[0] = position[0] + dp[0];
            proposed_position[1] = position[1] + dp[1];
        }
        
        position[0] = proposed_position[0]; position[1] = proposed_position[1];

        field.at<uchar>(std::floor(position[0]), std::floor(position[1])) = 255; // make new position bright (floor for sitting on bottom)

        if (disp_count >= display_interval) {
            cv::imshow("Particle Simulation", field);
            cv::waitKey(1);
            disp_count = 0;

            // cout << "Display" << endl;

            // Exit loop if 'q' or ESC is pressed
            if ((cv::waitKey(1) == 'q') || (cv::waitKey(1) == 27)) {
                break;
            }


            // Calculate elapsed time
            auto now = std::chrono::steady_clock::now();
            auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();

            // Break if elapsed time is too long
            if (elapsed_seconds >= secs_timeout) {
                std::cout << secs_timeout << " seconds have elapsed: closing window" << std::endl;
                break;
            }
        }
        disp_count += 1;

        v[0] *= air_res; v[1] *= air_res; // apply air resistance

        if ((round(position[0]) == 0) || (round(position[0]) == dims[0]) || (round(position[1]) == 0) || (round(position[1]) == dims[1])) {
            v[0] *= fric; v[1] *= fric; // friction
        }

    }

    cout << "     {*}~ THE END ~{*}" << endl;

    return 0;
    
}