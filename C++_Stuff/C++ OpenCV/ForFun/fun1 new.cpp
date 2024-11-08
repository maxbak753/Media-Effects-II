// First Program For Fun (imagination experiment)
// Maxwell Bakalos 10/10/2024

#include <iostream>             // Input-Output Stream
#include <opencv2/opencv.hpp>   // Open Computer Vision
#include <filesystem>           // print working directory
#include <cmath>                // pow() exponents
#include <chrono>               // elapsed time
#include <matplot/matplot.h>    // MatPlot++

// #ifndef M_PI
// #define M_PI 3.14159265358979323846
// #endif

using namespace cv;
using namespace std;

// Functions
std::tuple<int, int, int> choose_filter(int dims[2]);
cv::Mat gauss_kernel(int k_size, double a, double sigma_x, double sigma_y, bool normalize);
cv::Mat vert_line_kernel(int k_size);
cv::Mat subplot_stitch(const std::vector<cv::Mat>& images, int rows, int cols);
cv::Mat GameOfLifeEffect(cv::Mat& frame, cv::Mat& im_out, cv::Mat& k, int iter_GOL, int dims[2]);

// Main
int main(int argc, char** argv ) {
    cout << "Hello!" << endl;
    cout << "Current working directory: " << filesystem::current_path() << endl;

    // Open the default camera (usually webcam at index 0)
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the webcam." << std::endl;
        return -1;
    }

    cv::Mat frame;
    cap >> frame;  // Capture a new frame from the webcam

    if (frame.empty()) {
        std::cerr << "Error: Could not retrieve frame." << std::endl;
    }

    // -----------------------------
    // CONVOLUTION

    // Dimensions of Image
    int dims[2] = {frame.cols, frame.rows}; // {width, height}
    cout << "Dimensions: " << dims[0] << "x" << dims[1] << " (dims[0], dims[1])" << endl;

    // Choose the filter type
    int filter_type; // # index denoting the type of filter used
    int k_size; // must be odd (the side length in pixels of the square convolution kernel)
    int iter_GOL; // # of iterations for the Game Of Life effect
    tie(filter_type, k_size, iter_GOL) = choose_filter(dims);

    // Create Specified Kernel...
    cv::Mat k; // kernel matrix
    double sigma_x = k_size * 0.3, sigma_y = k_size * 0.3; // sigma is the sqrt{variance} for each respective direction
    bool conv_valid = true;
    bool option_valid = true;
    int secs_timeout = 30; // seconds after which the webcam window closes
    switch (filter_type) {
        case 1: // Box Blur
            cout << "Box Blur" << endl;
            k = cv::Mat::ones(k_size, k_size, CV_32F) * (pow(k_size, -2)); // Box Blur Kernel
            break;
        case 2: // Gaussian Blur
            cout << "Gaussian Blur" << endl;
            k = gauss_kernel(k_size, 1, sigma_x, sigma_y, true); // Gaussian Blur Kernel
            break;
        case 3: // Vertical Line Blur
            cout << "Vertical Line Blur" << endl;
            k = vert_line_kernel(k_size);
            break;
        case 4: // Game Of Life Effect
            cout << "Game Of Life Effect" << endl;
            k = gauss_kernel(k_size,1,3,3,false) - gauss_kernel(k_size,1,1,1,false); // subtract gaussians
            k /= cv::sum(k); // normalize
            conv_valid = false;
            break;
        default:
            cout << "The option you chose does not exist!\n>:(" << endl;
            conv_valid = false;
            option_valid = false;
            break;
    }

    // If the user chose a valid option...
    if (option_valid) {
        cv::namedWindow("Kernel", cv::WINDOW_NORMAL);
        imshow("Kernel", k*255);
        waitKey(3);
        cv::destroyAllWindows();

        // Create an output image to store the result
        cv::Mat im_out;

        // Record the start time
        auto start = std::chrono::steady_clock::now();

        cout << "(Press & Hold 'q' or ESC to exit)" << endl;
        
        // Whie "q" or ESC are not pressed... 
        while (true) {
            // Capture new frame from webcam
            cap >> frame;
            if (frame.empty()) {
                std::cerr << "Error: Could not retrieve frame." << std::endl;
                break;
            }

            // Appy Chosen Filter
            if (conv_valid) {
                // Perform convolution
                cv::filter2D(frame, im_out, CV_32F, k);
            } else if ((!conv_valid) && (filter_type == 4)) {
                // Run the Game Of Life Effect
                im_out = GameOfLifeEffect(frame, im_out, k, iter_GOL, dims);
            }

            if (! im_out.empty()) {
                // Convert the output image to the same type as the input image
                im_out.convertTo(im_out, frame.type());

                // Create a Subplot
                std::vector<cv::Mat> im__im_out = {frame, im_out}; // Put images in a vector
                cv::Mat subplot = subplot_stitch(im__im_out, 1, 2); // make plot image

                // Display Subplot
                cv::namedWindow("Subplot: OG Image, Convolved Image", cv::WINDOW_NORMAL); // use this to allow resizing
                cv::imshow("Subplot: OG Image, Convolved Image", subplot); // show image
                cv::resizeWindow("Subplot: OG Image, Convolved Image", subplot.cols, subplot.rows); // Set the window to its actual size

                // cout << "END OF PROGRAM" << endl;
                // return 0;
            }
            else {
                cout << "Display Issue: The output image is empty" << endl;
                // return -1;
            }

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

    }
    else {
        cout << "Option Issue: invalid choice" << endl;
        return -1;
    }

    cap.release();
    cv::destroyAllWindows();
    cout << "~*{ THE END }*~" << endl;
    return 0;
    
}

// -------------------------
// FUNCTIONS

std::tuple<int, int, int> choose_filter(int dims[2]) {
    /*  ARGUMENTS
        dims = dimensions of the image (width, height)
    */
    cout << "~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~ ~*~" << endl;
    cout << "Filter options...\n[1] Box Blur\n[2] Gaussian Blur\n[3] Vertical Line Blur\n[4] Game of Life Effect\nChoose a filter (enter the number): ";
    int filter_choice = 1;
    cin >> filter_choice;

    int filt_size;
    bool filt_size_valid = false;

    int while_count = 0;
    while (!filt_size_valid) {
        if (while_count < 10) {
            cout << "Select a blurring filter size (odd number): ";
            cin >> filt_size;
            if (filt_size % 2) {
                if (filt_size < min(dims[0], dims[1])) {
                    if (filt_size > 1) {
                        filt_size_valid = true;
                    } else {
                        cout << "Filter Size is TOO SMALL! Try again..." << endl;
                    }
                } else {
                    cout << "Filter Size is TOO BIG! Try again..." << endl;
                }
            } else {
                cout << "Filter Size must be an ODD NUMBER! Try again ..." << endl;
            }
        } else {
            cout << "Failed too many times (" << while_count << ") --> Filter Size to 5." << endl;
            filt_size = 5;
            filt_size_valid = true;
        }
        while_count += 1;
    }

    // Iterations for Game Of Life Effect
    int iter_GOL = 1;
    if (filter_choice == 4) {
        cout << "How many iterations?: ";
        cin >> iter_GOL;
    }

    // int filter_properties[2] = {filter_choice, filt_size};
    return std::make_tuple(filter_choice, filt_size, iter_GOL);
}

cv::Mat gauss_kernel(int k_size, double a, double sigma_x, double sigma_y, bool normalize) {
    /*  ARGUMENTS
        k_size = kernel size (length of square side)
        sigma_x = sigma for x-direction
        sigma_y = sigma for y-direction
    */

    // Create a kernel of the specified size
    cv::Mat kernel = cv::Mat::zeros(k_size, k_size, CV_32F);

    // Create 2D Gaussian Function
    int half_k_sz = k_size / 2;
    double gauss_k_sum = 0; // sum of kernel values (for normalization)
    // Populate the kernel with Gaussian values
    for (int y = -half_k_sz; y <= half_k_sz; ++y) {
        for (int x = -half_k_sz; x <= half_k_sz; ++x) {
            kernel.at<float>(y+half_k_sz, x+half_k_sz) = static_cast<float>( exp( -( (x*x)/(2*sigma_x*sigma_x) ) - ( (y*y)/(2*sigma_y*sigma_y) ) ) );
            // gauss_k_sum += kernel.at<float>(y+half_k_sz, x+half_k_sz); // get sum of kernel elements
        }
    }

    // Amplitude Scaling
    kernel *= a;

    if (normalize) {
        // Normalize
        // kernel /= gauss_k_sum;
        kernel /= cv::sum(kernel);
    }

    return kernel;
}

cv::Mat vert_line_kernel(int k_size) {
    cv::Mat kernel = cv::Mat::zeros(k_size, k_size, CV_32F);

    cv::Rect vLine(k_size/2, 0, 1, k_size);

    // kernel(vLine) = 1 / (vLine.width * vLine.height); // normalize
    kernel(vLine).setTo(1.0/((double)(vLine.width * vLine.height)));

    return kernel;
}

cv::Mat subplot_stitch(const std::vector<cv::Mat>& images, int rows, int cols) {
    /*  ARGUMENTS
        images = vector (std::vector) of images (cv::Mat)
        rows = # of rows of images in the final subplot
        cols = # of cols in the final subplot
    */

    // Check if the number of images matches the specified rows and columns
    if (images.size() != rows * cols) {
        std::cerr << "Error: Number of images does not match rows * cols." << std::endl;
        return cv::Mat(); // Return an empty matrix
    }

    // Get the dimensions of the first image (assume all images are the same size)
    int height = images[0].rows;
    int width = images[0].cols;

    // Create a larger image to hold the sub-images
    cv::Mat combined_im_array(rows * height, cols * width, images[0].type());

    // Copy images into the combined image
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            images[r * cols + c].copyTo(combined_im_array(cv::Rect(c * width, r * height, width, height)));
        }
    }

    return combined_im_array;
}


cv::Mat GameOfLifeEffect(cv::Mat& frame, cv::Mat& im_out, cv::Mat& k, int iter_GOL, int dims[2]) {
    // cout << "GOL...";
    // Create matrices to store the three channels
    std::vector<cv::Mat> channels_in(3, cv::Mat(dims[1], dims[0], CV_32F));
    std::vector<cv::Mat> channels_out(3, cv::Mat(dims[1], dims[0], CV_32F));

    // Split the image into B, G, R channels
    cv::Mat im_float;
    frame.convertTo(im_float, CV_64F, 1.0 / 255.0);
    // frame.convertTo(im_float, CV_32F, 1.0 / 255.0); // I want to use 32F but it turns the output black & white!
    cv::split(im_float, channels_in); // extract each color channel from the image

    float min_bound = static_cast<float>(0.2);  // lower bound (0 below)
    float max_bound = static_cast<float>(0.45); // upper bound (? I forget)
    float bound_diff = max_bound - min_bound;   // ???
    float shx = min_bound;                      // x shift
    float shy = static_cast<float>(0.5);        // y shift
    float scale = static_cast<float>(0.5);      // scale coefficient
    float pi_f = static_cast<float>(3.14159265358979323846); // π (pi)

    for (int l = 0; l < iter_GOL; l++) {
        for (int rgb = 0; rgb < 3; rgb++) {

            cv::Mat im_c = channels_in[rgb];
            cv::Mat x = im_c.clone();
            cv::filter2D(im_c, x, CV_32F, k);
            // (SKIP CROPPING for now)
            // x = x(n_k+1:end-n_k, n_k+1:end-n_k);

            // Ensure x is of type CV_32F (if not already)
            if (x.type() != CV_32F) {
                cout << "x (color channel " << rgb << ") is not CV_32F!!! Converting now." << endl;
                x.convertTo(x, CV_32F);
            }

            float idk = static_cast<float>(  (1.0/(bound_diff*2.0))*2.0*pi_f  );

            cv::Mat y = x.clone();

            // Lambda Function "[=]" captures external variables shx and bound_diff
            y.forEach<float>([=](float &val, const int * position) -> void {
                // if scale or shy are applied after the loop the result is different (no full black colors)
                val = ((-std::cos(idk * (val - shx))) * scale) + shy;
            });

            // Create a mask where x >= min_bound (1 where true, 0 where false)
            cv::Mat lessThanMask = (x >= min_bound);

            // Ensure the mask is of the desired type (CV_8U for binary mask)
            lessThanMask.convertTo(lessThanMask, CV_8U);

            // Set y to 0 wherever the mask is 0 (where x < min_bound)
            y.setTo(0, lessThanMask == 0);  // Invert mask to match condition

            channels_out[rgb] = y;
        }
        // Update input image for next loop
        channels_in = channels_out;
    }
    
    // Finalize Image (finishing touches)
    cv::merge(channels_out, im_out); // merge color channels
    cv::normalize(im_out, im_out, 0, 255, cv::NORM_MINMAX); // 0-255 range normalization
    
    // cout << " Done." << endl;
    return im_out;
}